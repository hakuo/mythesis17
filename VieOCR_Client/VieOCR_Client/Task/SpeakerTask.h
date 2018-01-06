#ifndef SPEAKERTASK_H
#define SPEAKERTASK_H

#include "TaskThread.h"

class SpeakerTask: public TaskThread
{
public:
    SpeakerTask();
    ~SpeakerTask();
    virtual void TaskHandler();
    virtual bool readyToRun();

private:

};

#endif // SPEAKERTASK_H
