#include "OCR_Task.h"
#include "OCR/OCR_Factory.h"

OCRTask::OCRTask()
{
    mOCRinstance = NULL;
    mImgProc = NULL;
    mQueue.txQueue = -1;
    mQueue.rxQueue = -1;
}

OCRTask::OCRTask(OCR::ocr_type_t ocr_type)
{
    mOCRinstance = NULL;
    mImgProc = NULL;
    mOCRinstance = OCRFactory::Get()->createOCR(ocr_type);
    mImgProc = new ImageProcessing();
    mQueue.txQueue = openTxQueue(TTS_QUEUE);
    mQueue.rxQueue = openRxQueue(OCR_QUEUE);
}

OCRTask::~OCRTask()
{
    if(mOCRinstance)
    {
        delete mOCRinstance;
        mOCRinstance = NULL;
    }

    if(mImgProc)
    {
        delete mImgProc;
        mImgProc = NULL;
    }
    closeMessageQueue(mQueue.txQueue);
    closeMessageQueue(mQueue.rxQueue);
    // remove its queue
    mq_unlink(OCR_QUEUE);
}

/*
 * @function: readyToRun
 * @description: condition to run OCRTask
 * (create a thread handles OCRTask)
 * @author: Duong Hac Cuong
 * @created: December 16, 2017
 */
bool OCRTask::readyToRun()
{
    return ((mOCRinstance != NULL)  && (mImgProc != NULL)
            &&  (mQueue.txQueue != -1) && (mQueue.rxQueue != -1));
}

/*
 * @function: TaskHandler
 * @description: Main function of OCRTask
 * @author: Duong Hac Cuong
 * @created: December 16, 2017
 */
void OCRTask::TaskHandler()
{
    message_t txMsg;
    message_t rxMsg;
    uint8_t buffer[MAX_MQUEUE_SIZE];
    ssize_t szLen;

    // Step 1: Check rxQueue to receive image path
    szLen = popMessageQueue(mQueue.rxQueue, (char *)buffer);
    if(szLen <= 0)
    {
        //QDebug() << "OCRTask: Queue empty";
        return;
    }
    memset(&rxMsg, 0, sizeof(message_t));
    memcpy(&rxMsg, buffer, sizeof(message_t));

    // Step 2: preprocessing
    if(!mImgProc->loadImage((char *)rxMsg.data))
    {
        qDebug() << " OCRTask::TaskHandler(): loadImage false";
        return;
    }

    // Step 3: runOCR
    mOCRinstance->setInput((char *)rxMsg.data, mImgProc->mImageGray);
    qDebug() << "OCR Processing";
    mOCRinstance->run();
    qDebug() << "OCR done";

    // Step 3: Postprocessing


    // Step 6: push output to txQueue
    std::string outTxt = mOCRinstance->getOutput();     //TODO: get output from postprocessing

    memset(&txMsg, 0, sizeof(message_t));
    txMsg.msg_id = rxMsg.msg_id;
    memcpy(txMsg.data, outTxt.c_str(), outTxt.length());

    pushMessageQueue(mQueue.txQueue, (char *)&txMsg, sizeof(message_t));
}



































