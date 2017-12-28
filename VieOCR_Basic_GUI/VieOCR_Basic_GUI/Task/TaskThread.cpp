#include "TaskThread.h"
#include "pthread.h"
#include <QDebug>

#define MQUEUE_PERMISSIONS 0644
#define MAX_MQUEUE_NO 10



TaskThread* TaskThread::m_me=nullptr;

TaskThread::TaskThread()
{
    mThreadID=0;
    mThreadTerminate=true;
    mQueue.rxQueue = -1;
    mQueue.txQueue = -1;
}

TaskThread::~TaskThread()
{
    closeMessageQueue(mQueue.rxQueue);
    closeMessageQueue(mQueue.txQueue);
}

void TaskThread::run()
{
    if(readyToRun())
    {
        /* Create new thread to handle an infinity loop */
        mThreadTerminate = false;       // run()
        if(pthread_create(&mThreadID, nullptr, TaskThread::_thread_, this) < 0)
        {
            perror("Create thread failed");
            qDebug() << "TaskThread::run(): Create thread failed";
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
        TaskHandler();
    }
}

mqd_t TaskThread::openRxQueue(const char *pName)
{
    return openMessageQueue(pName, (O_CREAT | O_RDONLY | O_NONBLOCK));
}

mqd_t TaskThread::openTxQueue(const char *pName)
{
    return openMessageQueue(pName, (O_CREAT | O_WRONLY | O_NONBLOCK));
}

mqd_t TaskThread::openMessageQueue(const char *pName, int32_t flag)
{
    mqd_t retQid = (mqd_t)-1;
    struct mq_attr attr;

    if (NULL != pName) {
        /* initialize the queue attributes */
        attr.mq_flags = 0;
        attr.mq_maxmsg = MAX_MQUEUE_NO;
        attr.mq_msgsize = MAX_MQUEUE_SIZE;
        attr.mq_curmsgs = 0;

        if ((retQid = mq_open(pName, flag, MQUEUE_PERMISSIONS, &attr)) == -1) {
            //std::cout << "Queue open error " << pName << std::endl;
            qDebug() << "openMessageQueue(): Queue open error " << pName;
        }
    }

    return retQid;
}

void TaskThread::closeMessageQueue(mqd_t &mqQid)
{
    if (-1 != mqQid)
    {
        mq_close(mqQid);
        mqQid = -1;
    }
}

void TaskThread::pushMessageQueue(mqd_t mqQidDes, const char *pOutBuf, size_t szLen)
{
    if ((-1 != mqQidDes) && (pOutBuf != NULL) && (szLen > 0))
    {
        mq_send(mqQidDes, pOutBuf, szLen, 0);
    }
    else
    {
        qDebug() << "pushMessageQueue(): Invalid input";
    }
    return;
}

ssize_t TaskThread::popMessageQueue(mqd_t mqQidFrom, char *pMsgBuf)
{
    ssize_t nRecvBytes = -1;

    if (NULL == pMsgBuf) {
        qDebug() << "Invalid buffer for storing message";
    }

    if (-1 != mqQidFrom) {
        nRecvBytes = mq_receive(mqQidFrom, pMsgBuf, MAX_MQUEUE_SIZE, 0);
    }

    if (-1 == nRecvBytes) {
        qDebug() << "Receive message from message queue has been failed";
    }
    return nRecvBytes;
}
//bool TaskThread::popTxQueue(message_t &msg)
//{
//    bool ret;
//    if(txQueue.empty())
//    {
//        ret = false;
//    }
//    else
//    {
//        msg=txQueue.front();
//        txQueue.pop();
//        ret = true;
//    }
//    return ret;
//}

//void TaskThread::pushTxQueue(message_t msg)
//{
//    txQueue.push(msg);
//}

//bool TaskThread::popRxQueue(message_t &msg)
//{
//    bool ret;
//    if(rxQueue.empty())
//    {
//        ret = false;
//    }
//    else
//    {
//        msg=rxQueue.front();
//        rxQueue.pop();
//        ret = true;
//    }
//    return ret;
//}

//void TaskThread::pushRxQueue(message_t msg)
//{
//    rxQueue.push(msg);
//}

