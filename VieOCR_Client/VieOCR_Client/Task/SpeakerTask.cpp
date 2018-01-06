#include "SpeakerTask.h"
#include "Sound/Sound.h"

SpeakerTask::SpeakerTask()
{
    mQueue.rxQueue = openRxQueue(SPK_QUEUE);
}

SpeakerTask::~SpeakerTask()
{
    closeMessageQueue(mQueue.rxQueue);
    mq_unlink(SPK_QUEUE);
}

void SpeakerTask::TaskHandler()
{
    message_t rxMsg;
    uint8_t buffer[MAX_MQUEUE_SIZE] = {0};
    ssize_t szLen;
    szLen = popMessageQueue(mQueue.rxQueue, (char *)buffer);
    if(szLen <= 0)
    {
        std::cout << "SpeakerTask: Queue empty" << std::endl;
        return;
    }

    memset(&rxMsg, 0, sizeof(message_t));
    memcpy(&rxMsg, buffer, sizeof(message_t));
    iHearTech::Sound::play((char *)rxMsg.data);
}

bool SpeakerTask::readyToRun()
{
    return (mQueue.rxQueue != -1);
}
