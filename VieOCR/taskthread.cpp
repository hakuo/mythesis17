#include "taskthread.h"
#include "pthread.h"

TaskThread* TaskThread::m_me=nullptr;

TaskThread::TaskThread()
{
    mThreadID=0;
    mThreadTerminate=false;
}

TaskThread::~TaskThread()
{
}

void TaskThread::run()
{
    if(readyToRun())
    {
        /* Create new thread to handle an infinity loop */
        if(pthread_create(&mThreadID, nullptr, TaskThread::_thread_, this) < 0)
        {
            perror("Create thread failed");
        }
    }
}

void TaskThread::stop()
{
    if(mThreadID)
    {
        mThreadTerminate=true;
        pthread_join(mThreadID, nullptr);
        mThreadID=0;
    }
}

void* TaskThread::_thread_(void *arg)
{
    m_me = reinterpret_cast<TaskThread*>(arg);
    m_me->ThreadLoop();
    return nullptr;
}

void TaskThread::ThreadLoop()
{
    while(!mThreadTerminate)
    {
        this->TaskHandler();
    }
}

bool TaskThread::popTxQueue(message_t &msg)
{
    if(txQueue.empty())
    {
        return false;
    }
    else
    {
        msg=txQueue.front();
        txQueue.pop();
        return true;
    }
}

void TaskThread::pushTxQueue(message_t msg)
{
    txQueue.push(msg);
}

bool TaskThread::popRxQueue(message_t &msg)
{
    if(rxQueue.empty())
    {
        return false;
    }
    else
    {
        msg=rxQueue.front();
        rxQueue.pop();
        return true;
    }
}

void TaskThread::pushRxQueue(message_t msg)
{
    rxQueue.push(msg);
}
