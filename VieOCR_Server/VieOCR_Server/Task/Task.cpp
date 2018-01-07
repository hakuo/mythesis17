#include "Task.h"
#include "OCR/OCR.h"

Task::Task(OCR::ocr_type_t type)
{
    pTcpServer = new TcpServerTask;
    pOCR = new OCRTask(type);
    pTTS = new TTSTask;
    pTcpClient = new TcpClientTask;
}

Task::~Task()
{
    delete pTcpServer;
    delete pOCR;
    delete pTTS;
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
    pOCR->run();
    pTTS->run();
    pTcpClient->run();
}

void Task::stopAllTask()
{
    if(isTaskRun(pTcpClient))
    {
        pTcpClient->stop();
    }

    if(isTaskRun(pOCR))
    {
        pOCR->stop();
    }

    if(isTaskRun(pTTS))
    {
        pTTS->stop();
    }

    if(isTaskRun(pTcpServer))
    {
        pTcpServer->stop();
    }
}

bool Task::isTaskRun(TaskThread *task)
{
    return !(task->mThreadTerminate);
}
