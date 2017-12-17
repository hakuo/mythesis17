/*
 * * TTSTask (Text To Speech) reads context from a text file and speaks out
 * * Dependencies: T.B.D
 * * Input: a text file which needs to speak out
 * * Output: Speak out the context in txt file
 * * Author: Duong Hac Cuong (BKU)
 * * Created: December 16, 2017
 */
#ifndef TTSTASK_H
#define TTSTASK_H

#include "taskthread.h"
#include "common.h"

#ifdef UT_TEST
#define private public
#endif
class TTSTask : public TaskThread
{
public:
    TTSTask();
    ~TTSTask();

private:
    virtual bool readyToRun();
    virtual void TaskHandler();

};

#endif // TTSTASK_H
