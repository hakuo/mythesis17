#include "Task.h"

Task::Task()
{

}

Task::~Task()
{

}

void Task::initParameter(int tcpPort, int tcpListenNum)
{
    pTcpServer->setListenNum(tcpListenNum);
    pTcpServer->setListenPort(tcpPort);
}

void Task::runAllTask()
{
    pTcpServer->run();
    pOCR->run();
    pTTS->run();
}

bool Task::isTaskRun(TaskThread *task)
{
    return !(task->mThreadTerminate);
}
