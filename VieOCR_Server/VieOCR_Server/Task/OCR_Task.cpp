#include "OCR_Task.h"
#include "OCR/OCR_Factory.h"

OCRTask::OCRTask()
{
    pOCRinstance = NULL;
    mQueue.txQueue = -1;
    mQueue.rxQueue = -1;
}

OCRTask::OCRTask(OCR::ocr_type_t ocr_type)
{
    pOCRinstance = NULL;
    pOCRinstance = OCRFactory::Get()->createOCR(ocr_type);
    mQueue.txQueue = openTxQueue(TTS_QUEUE);
    mQueue.rxQueue = openRxQueue(OCR_QUEUE);
}

OCRTask::~OCRTask()
{
    if(pOCRinstance)
    {
        delete pOCRinstance;
        pOCRinstance = NULL;
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
    return ((pOCRinstance != NULL) &&  (mQueue.txQueue != -1) && (mQueue.rxQueue != -1));
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
    uint8_t buffer[MAX_MQUEUE_SIZE] = {0};
    ssize_t szLen;

    // Step 1: Check rxQueue to receive image path
    szLen = popMessageQueue(mQueue.rxQueue, (char *)buffer);
    if(szLen <= 0)
    {
        //std::cout << "OCRTask: Queue empty";
        return;
    }
    memset(&rxMsg, 0, sizeof(message_t));
    memcpy(&rxMsg, buffer, sizeof(message_t));

    // Step 2: Pre-processing: deSkew and lines segmentation
    cv::Mat img_tmp;
    std::string outTxt;
    std::vector<cv::Mat> lines;
    pOCRinstance->loadImage(img_tmp, (char *)rxMsg.data);
    pOCRinstance->deSkew(img_tmp, img_tmp);
    pOCRinstance->lineSegment(lines, img_tmp);
    for(size_t i=0; i<lines.size(); ++i)
    {
//        cv::imshow("line", lines[i]);
//        cv::waitKey();
        // Step 3: doOCR in each segmented lines and push to TTS
        outTxt = pOCRinstance->createTxt(lines[i]);
        if(outTxt.length() > 0)
        {
            memset(&txMsg, 0, sizeof(message_t));
            memcpy(txMsg.msg_id, rxMsg.msg_id, MSG_ID_LENGTH);
            memcpy(txMsg.data, outTxt.c_str(), outTxt.length());
            pushMessageQueue(mQueue.txQueue, (char *)&txMsg, sizeof(message_t));
            std::cout << "push a queue to TTS" << std::endl;
        }
    }
    //std::string outTxt = pOCRinstance->createTxt((char *)rxMsg.data);

}



































