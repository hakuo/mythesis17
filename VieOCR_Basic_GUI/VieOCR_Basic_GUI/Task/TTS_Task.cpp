#include "TTS_Task.h"

TTSTask::TTSTask()
{
    mTTSinstance = new iHearTech::TTS();
    mQueue.txQueue = openTxQueue(TCP_QUEUE);
    mQueue.rxQueue = openRxQueue(TTS_QUEUE);
}

TTSTask::~TTSTask()
{
    if(mTTSinstance)
    {
        delete mTTSinstance;
        mTTSinstance = NULL;
    }
    closeMessageQueue(mQueue.txQueue);
    closeMessageQueue(mQueue.rxQueue);
    // remove its queue
    mq_unlink(TTS_QUEUE);
}

/*
 * @function: readyToRun
 * @description: condition to run TTSTask
 * (create a thread handle TTSTask)
 * @author: Duong Hac Cuong
 * @created: December 16, 2017
 */
bool TTSTask::readyToRun()
{
    return ((mTTSinstance != NULL) && (mQueue.txQueue != -1) && (mQueue.rxQueue != -1));
}

/*
 * Input TTS_QUEUE
 * Output TCP_QUEUE
 * @function: TaskHandler
 * @description: Main function of TTSTask
 * @author: Duong Hac Cuong (BKU)
 * @created: December 16, 2017
 */
void TTSTask::TaskHandler()
{
    message_t txMsg;
    message_t rxMsg;
    uint8_t buffer[MAX_MQUEUE_SIZE];
    ssize_t szLen;

    // Step 1: check rxQueue to receive txt path
    szLen = popMessageQueue(mQueue.rxQueue, (char *)buffer);
    if(szLen <= 0)
    {
        //QDebug() << "TTSTask: Queue empty";
        return;
    }
    memset(&rxMsg, 0, sizeof(message_t));
    memcpy(&rxMsg, buffer, sizeof(message_t));

    std::string wavOut = mTTSinstance->createWav((char *)rxMsg.data);
    if(wavOut == "")
    {
        memset(&txMsg, 0, sizeof(message_t));
        txMsg.msg_id = rxMsg.msg_id;
        memcpy(txMsg.data, wavOut.c_str(), wavOut.length());
        pushMessageQueue(mQueue.txQueue, (char *)&txMsg, sizeof(message_t));
    }
}
