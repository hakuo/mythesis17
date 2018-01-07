#ifndef TASK_H
#define TASK_H

#include "CameraTask.h"
#include "SpeakerTask.h"
#include "TcpServer_Task.h"
#include "TcpClient_Task.h"

class Task
{
public:
    Task();
    ~Task();
    void initParameter(int tcpPort, int tcpListenNum, int camno, const char* serv_addr);
    bool isTaskRun(TaskThread* task);
    void runAllTask();
    void stopAllTask();
    void capture();

private:
    TcpServerTask *pTcpServer;
    TcpClientTask *pTcpClient;
    CameraTask *pCam;
    SpeakerTask *pSpeaker;
};

#endif // TASK_H
