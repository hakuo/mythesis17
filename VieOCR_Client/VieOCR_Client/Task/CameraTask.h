#ifndef CAMERATASK_H
#define CAMERATASK_H

#include "TaskThread.h"
#include "CameraMgr/CameraMgr.h"

class CameraTask: public TaskThread
{
public:
    CameraTask();
    ~CameraTask();

    virtual bool readyToRun();
    virtual void TaskHandler();
    virtual void ThreadLoop();  //override
    virtual void stop();        //override
    bool init(int camno);
    void capture();
private:
    CameraMgr* pCam;

};

#endif // CAMERATASK_H
