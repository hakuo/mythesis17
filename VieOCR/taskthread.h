#ifndef TASKTHREAD_H
#define TASKTHREAD_H

#include "common.h"
#include <queue>

class TaskThread
{
public:
    TaskThread();
    ~TaskThread();
    void run();
    void stop();
    bool popTxQueue(message_t& msg);
    void pushRxQueue(message_t msg);

protected:
    virtual bool readyToRun()=0;
    virtual void TaskHandler()=0;
    bool popRxQueue(message_t& msg);
    void pushTxQueue(message_t msg);

private:
    bool mThreadTerminate;
    pthread_t mThreadID;
    static TaskThread* m_me;
    static void* _thread_(void *arg);
    void ThreadLoop();
    queue<message_t> txQueue;
    queue<message_t> rxQueue;
};

#endif // TASKTHREAD_H
