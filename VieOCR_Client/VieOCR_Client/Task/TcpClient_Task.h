#ifndef TCPCLIENT_TASK_H
#define TCPCLIENT_TASK_H

#include "TaskThread.h"
#include "TCP/TcpClient/TcpClient.h"


class TcpClientTask: public TaskThread
{
public:
    TcpClientTask();
    ~TcpClientTask();

    virtual bool readyToRun();
    virtual void TaskHandler();
    void setServerAddress(const char* addr);

private:
    TcpClient* pTcpClient;
    std::string serv_addr;
};

#endif // TCPCLIENT_TASK_H
