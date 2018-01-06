#include "Task.h"
//#include "OCR/OCR.h"

Task::Task()
{
    pTcpServer = new TcpServerTask;
//    pOCR = new OCRTask(type);
//    pTTS = new TTSTask;
    pTcpClient = new TcpClientTask;
}

Task::~Task()
{
    delete pTcpServer;
    delete pTcpClient;
}

void Task::initParameter(int tcpPort, int tcpListenNum)
{
    pTcpServer->setListenNum(tcpListenNum);
    pTcpServer->setListenPort(tcpPort);
}

void Task::runAllTask()
{
    pTcpServer->run();
    pTcpClient->run();
}

bool Task::isTaskRun(TaskThread *task)
{
    return !(task->mThreadTerminate);
}
