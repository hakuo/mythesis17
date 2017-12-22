#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <string>
#include <fstream>
#include "tcpsocket.h"

class TcpServer
{
public:
    TcpServer();
    ~TcpServer();

    int mServerSock;
    bool mTerminate;
    bool initSock(int portno, int listen_num);
    void run();
    void stop();

private:
    TcpSocket::request_t mState;
    TcpSocket::file_t mFile;
    void closeSock(int &sockfd);
    uint8_t* handleMessage(const TcpSocket::tcp_pkg_t* package);
    uint8_t* startDownload(const uint8_t* data);
    uint8_t* transferFile(const uint8_t* data);
    uint8_t* endDownload();
    virtual void notifyFileAvailable(const std::string filepath);
};

#endif // TCPSERVER_H
