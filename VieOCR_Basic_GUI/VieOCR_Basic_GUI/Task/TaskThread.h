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
        std::string msg_id;
        uint8_t data[256];
    } message_t;

    typedef struct
    {
        mqd_t txQueue;
        mqd_t rxQueue;
    }queue_info_t;

    virtual void run();
    virtual void stop();
    bool mThreadTerminate;
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

    //bool popRxQueue(message_t& msg);
    //void pushTxQueue(message_t msg);

private:
    pthread_t mThreadID;
    static TaskThread* m_me;
    static void* _thread_(void *arg);
    //std::queue<message_t> txQueue;
    //std::queue<message_t> rxQueue;
};

#endif // TASKTHREAD_H
