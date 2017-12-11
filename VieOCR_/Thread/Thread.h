/*
 * Thread.h
 *
 *  Created on: Nov 27, 2017
 *      Author: cuongdh8
 */

#ifndef THREAD_H_
#define THREAD_H_

#include "../common.h"
#include <pthread.h>
#include <queue>

class Thread {
public:
    Thread();
    virtual ~Thread();
    void run();
    void stop();
    void pushRxQueue(message_t msg);
    void pushTxQueue(message_t msg);
    bool popRxQueue(message_t& msg);
    bool popTxQueue(message_t& msg);
    static Thread* m_me;

protected:
    queue<message_t> txQueue;
    queue<message_t> rxQueue;

private:
    virtual bool readyToRun() = 0;
    virtual void threadLoop() = 0;
    static void* _threadLoop_(void *arg);
    pthread_t mThreadID;
};

#endif /* THREAD_H_ */
