#ifndef TASKTHREAD_H
#define TASKTHREAD_H

#include "common.h"
#include <mqueue.h>
#include "TCP/TcpUtils/TcpUtils.h"
#define OCR_QUEUE "/OCR_Queue"  // mqueue of OCR Tool
#define TTS_QUEUE "/TTS_Queue"  // mqueue of TTS Tool
#define TCP_QUEUE "/TCP_Queue"  // mqueue of TCP Client

#define MAX_MQUEUE_SIZE 512

class TaskThread
{
public:
    TaskThread();
    virtual ~TaskThread();

    typedef struct
    {
        uint8_t msg_id[MSG_ID_LENGTH];
        uint8_t data[MSG_DATA_LENGTH];
    } message_t;

    typedef struct
    {
        mqd_t txQueue;
        mqd_t rxQueue;
    }queue_info_t;

    void run();
    virtual void stop();
    volatile bool mThreadTerminate;
    static mqd_t openTxQueue(const char* pName);
    static mqd_t openRxQueue(const char* pName);
    static mqd_t openMessageQueue(const char* pName, int32_t flag);
    static void closeMessageQueue(mqd_t &mqQid);
    static void pushMessageQueue(mqd_t mqQidDes, const char *pOutBuf, size_t szLen);
    static ssize_t popMessageQueue(mqd_t mqQidFrom, char *pMsgBuf);

protected:
    virtual bool readyToRun()=0;
    virtual void TaskHandler()=0;
    queue_info_t mQueue;
    virtual void ThreadLoop();
    bool isTaskRun;
    pthread_t mThreadID;

private:
    static TaskThread* m_me;
    static void* _thread_(void *arg);
};

#endif // TASKTHREAD_H
