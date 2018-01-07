#include "TcpClient_Task.h"

TcpClientTask::TcpClientTask()
{
    mQueue.rxQueue = -1;
    pTcpClient = NULL;
    mQueue.rxQueue = openRxQueue(TCP_QUEUE);
    pTcpClient = new TcpClient;
}

TcpClientTask::~TcpClientTask()
{
    if(pTcpClient != NULL)
    {
        delete pTcpClient;
        pTcpClient = NULL;
    }
    mq_unlink(TCP_QUEUE);
}

bool TcpClientTask::readyToRun()
{
    return (mQueue.rxQueue != -1) && (pTcpClient != NULL);
}

void TcpClientTask::TaskHandler()
{
    message_t rxMsg;
    uint8_t buffer[MAX_MQUEUE_SIZE];
    ssize_t szLen;

    // Step 1: Check rxQueue to receive image path
    szLen = popMessageQueue(mQueue.rxQueue, (char *)buffer);
    if(szLen <= 0)
    {
        /* Queue empty */
        return;
    }
    std::cout << "receive a queue from Camera" << std::endl;
    memset(&rxMsg, 0, sizeof(message_t));
    memcpy(&rxMsg, buffer, sizeof(message_t));
    pTcpClient->connectToServer(serv_addr.c_str(), TCP_PORT);
    pTcpClient->sendFile((char *)rxMsg.data);
    pTcpClient->closeSock();
}

void TcpClientTask::setServerAddress(const char *addr)
{
    if(addr != NULL)
    {
       serv_addr = addr;
    }
}
