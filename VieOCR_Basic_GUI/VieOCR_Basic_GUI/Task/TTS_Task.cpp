#include "TTS_Task.h"

TTSTask::TTSTask()
{
    mQueue.txQueue = openTxQueue(TCP_QUEUE);
    mQueue.rxQueue = openRxQueue(TTS_QUEUE);
}

TTSTask::~TTSTask()
{
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
    return (mQueue.txQueue != -1) && (mQueue.rxQueue != -1);
}

/*
 * @function: TaskHandler
 * @description: Main function of TTSTask
 * @author: Duong Hac Cuong (BKU)
 * @created: December 16, 2017
 */
void TTSTask::TaskHandler()
{

}
