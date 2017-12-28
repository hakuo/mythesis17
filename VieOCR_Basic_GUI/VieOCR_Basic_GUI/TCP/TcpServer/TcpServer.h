#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <string>
#include <fstream>
#include "TCP/TcpUtils/TcpUtils.h"
#include <map>

class TcpServer
{
public:
    TcpServer();
    ~TcpServer();

    int mServerSock;
    bool mTerminate;
    bool initSock(uint16_t portno, uint8_t listen_num);
    void run();
    void stop();

private:
    TcpUtils::request_t mState;
    TcpUtils::file_t mFile;
    std::map<int, TcpUtils::sock_info_t> sock_map;
    void closeSock(int &sockfd);
    void handleMessage(const TcpUtils::tcp_pkg_t* rxPackge, TcpUtils::tcp_pkg_t *txPackge);
    void startDownload(const uint8_t* data, TcpUtils::tcp_pkg_t *txPackage);
    void transferFile(const uint8_t* data, TcpUtils::tcp_pkg_t *txPackage);
    void endDownload(TcpUtils::tcp_pkg_t *txPackage);
    virtual void notifyFileAvailable(const std::string filepath);
};

#endif // TCPSERVER_H
