#include "Task.h"

Task::Task()
{
    pTcpServer = new TcpServerTask();
    pTcpClient = new TcpClientTask();
    pCam = new CameraTask();
    pSpeaker = new SpeakerTask();
}

Task::~Task()
{
    delete pTcpServer;
    delete pTcpClient;
    delete pCam;
    delete pSpeaker;
}

void Task::initParameter(int tcpPort, int tcpListenNum, int camno, const char *serv_addr)
{
    pTcpServer->setListenNum(tcpListenNum);
    pTcpServer->setListenPort(tcpPort);
    pCam->init(camno);
    pTcpClient->setServerAddress(serv_addr);
}

void Task::runAllTask()
{
    pTcpServer->run();
    pTcpClient->run();
    pCam->run();
    pSpeaker->run();
}

void Task::stopAllTask()
{
    if(isTaskRun(pTcpClient))
    {
        pTcpClient->stop();
    }

    if(isTaskRun(pCam))
    {
        pCam->stop();
    }

    if(isTaskRun(pSpeaker))
    {
        pSpeaker->stop();
    }

    if(isTaskRun(pTcpServer))
    {
        pTcpServer->stop();
    }
}

void Task::capture()
{
    pCam->capture();
}

bool Task::isTaskRun(TaskThread *task)
{
    return !(task->mThreadTerminate);
}
