#ifndef TASK_H
#define TASK_H

//#include "OCR_Task.h"
//#include "TTS_Task.h"
#include "TcpServer_Task.h"
#include "TcpClient_Task.h"

class Task
{
public:
    Task();
    ~Task();
    void initParameter(int tcpPort, int tcpListenNum);
    bool isTaskRun(TaskThread* task);
    void runAllTask();
private:
//    OCRTask *pOCR;
//    TTSTask *pTTS;
    TcpServerTask *pTcpServer;
    TcpClientTask *pTcpClient;


};

#endif // TASK_H
