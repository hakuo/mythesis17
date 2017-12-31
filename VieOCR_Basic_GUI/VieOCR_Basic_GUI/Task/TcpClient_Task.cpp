#include "TcpClient_Task.h"

TcpClientTask::TcpClientTask()
{
    mQueue.rxQueue = -1;
    pTcpClient = NULL;
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
    mQueue.rxQueue = openRxQueue(TCP_QUEUE);
    if(pTcpClient == NULL)
    {
        pTcpClient = new TcpClient;
    }
    return (mQueue.rxQueue != -1) && (pTcpClient != NULL);
}

void TcpClientTask::TaskHandler()
{
//    message_t rxMsg;
//    uint8_t buffer[MAX_MQUEUE_SIZE];
//    ssize_t szLen;

//    // Step 1: Check rxQueue to receive image path
//    szLen = popMessageQueue(mQueue.rxQueue, (char *)buffer);
//    if(szLen <= 0)
//    {
//        qDebug() << "TcpClientTask: Queue empty";
//        return;
//    }
//    memset(&rxMsg, 0, sizeof(message_t));
//    memcpy(&rxMsg, buffer, sizeof(message_t));
//    pTcpClient->connectToServer(rxMsg.msg_id.c_str(), TCP_PORT);
//    pTcpClient->sendFile((char *)rxMsg.data);
//    pTcpClient->closeSock();
}
