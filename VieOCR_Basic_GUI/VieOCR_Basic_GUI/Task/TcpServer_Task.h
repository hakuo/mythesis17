#ifndef TCPSERVERTASK_H
#define TCPSERVERTASK_H

#include "TaskThread.h"
#include "TCP/TcpServer/TcpServer.h"

class TcpServerTask: public TaskThread
{
public:
    TcpServerTask();
    virtual ~TcpServerTask();

    void setListenPort(int portno);
    void setListenNum(int num);
private:
    virtual bool readyToRun();
    virtual void TaskHandler();
    virtual void ThreadLoop();  // override
//    virtual void stop();        // override

    bool initSock(uint16_t portno, uint8_t listen_num);
    int mServerSock;
    int mListenPort;
    int mListenNum;

};

#endif // TCPSERVERTASK_H
