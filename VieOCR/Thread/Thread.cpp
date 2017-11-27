/*
 * Thread.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: cuongdh8
 */

#include "Thread.h"

Thread* Thread::m_me = NULL;

Thread::Thread() {
    // TODO Auto-generated constructor stub
    mThreadID = 0;
}

Thread::~Thread() {
    // TODO Auto-generated destructor stub
}

void Thread::run() {
    if(readyToRun()) {
        if(pthread_create(&mThreadID, NULL, _threadLoop_, this) < 0) {
            perror("Create thread failed");
        }
    }
}

void* Thread::_threadLoop_(void *arg) {
    m_me = reinterpret_cast<Thread*> (arg);
    m_me->threadLoop();
    return NULL;
}

void Thread::stop() {
    if(mThreadID) {
        pthread_cancel(mThreadID);
        mThreadID = 0;
    }
}

void Thread::pushRxQueue(message_t msg) {
    rxQueue.push(msg);
}

void Thread::pushTxQueue(message_t msg) {
    txQueue.push(msg);
}

bool Thread::popRxQueue(message_t& msg) {
    if(rxQueue.empty()) {
        return false;
    }
    else {
        msg = rxQueue.front();
        rxQueue.pop();
        return true;
    }
}

bool Thread::popTxQueue(message_t& msg) {
    if(txQueue.empty()) {
        return false;
    }
    else {
        msg = txQueue.front();
        txQueue.pop();
        return true;
    }
}
