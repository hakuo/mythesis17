#ifndef TASKTHREAD_H
#define TASKTHREAD_H

#include "common.h"
#include <mqueue.h>

#define OCR_QUEUE "/OCR_Queue"
#define TTS_QUEUE "/TTS_Queue"
#define TCP_QUEUE "/TCP_Queue"

#define MAX_MQUEUE_SIZE 512

class TaskThread
{
public:
    TaskThread();
    virtual ~TaskThread();

    typedef struct
    {
        uint8_t msg_id;
        uint8_t data[256];
    } message_t;

    typedef struct
    {
        mqd_t txQueue;
        mqd_t rxQueue;
    }queue_info_t;

    void run();
    void stop();
    //bool popTxQueue(message_t& msg);
    //void pushRxQueue(message_t msg);

protected:
    virtual bool readyToRun()=0;
    virtual void TaskHandler()=0;
    queue_info_t mQueue;
    mqd_t openTxQueue(const char* pName);
    mqd_t openRxQueue(const char* pName);
    mqd_t openMessageQueue(const char* pName, int32_t flag);
    void closeMessageQueue(mqd_t &mqQid);
    void pushMessageQueue(mqd_t mqQidDes, const char *pOutBuf, size_t szLen);
    ssize_t popMessageQueue(mqd_t mqQidFrom, char *pMsgBuf);


    //bool popRxQueue(message_t& msg);
    //void pushTxQueue(message_t msg);

private:
    bool mThreadTerminate;
    pthread_t mThreadID;
    static TaskThread* m_me;
    static void* _thread_(void *arg);
    void ThreadLoop();
    //std::queue<message_t> txQueue;
    //std::queue<message_t> rxQueue;
};

#endif // TASKTHREAD_H
