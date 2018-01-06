/*
 * How to use: Camera Task
 * Step 1: init() => Choose default camera
 * Step 2: run()
 * Step 3: capture() => Capture image and send to client_task
 *
 * ===========================================
 * Step 4: stop() => stop camera_task
 *
 */
#include "CameraTask.h"

CameraTask::CameraTask()
{
    pCam = NULL;
    mQueue.txQueue = -1;
    mQueue.txQueue = openTxQueue(TCP_QUEUE);
}

CameraTask::~CameraTask()
{
    this->stop();
}

bool CameraTask::readyToRun()
{
    return ((pCam != NULL) && (mQueue.txQueue != -1));
}

bool CameraTask::init(int camno)
{
    if(pCam != NULL)
    {
        std::cout << "Camera has already created" << std::endl;
        return false;
    }
    pCam = new CameraMgr();
    pCam->openCam(camno);
    return true;
}

void CameraTask::stop()
{
    if(pCam == NULL)
    {
        return;
    }
    pCam->stopCam();
    pthread_join(mThreadID, NULL);
    delete pCam;
}

void CameraTask::TaskHandler()
{
    pCam->startCam();
}

void CameraTask::capture()
{
    std::string img_path = pCam->capture();
    if(mQueue.txQueue != -1)
    {
        message_t msg;
        memset(&msg, 0 ,sizeof(msg));
        strncpy((char *)msg.data, img_path.c_str(), img_path.length());
        pushMessageQueue(mQueue.txQueue, (char *)&msg, sizeof(msg));
    }
}

void CameraTask::ThreadLoop()
{
    this->TaskHandler();
}
