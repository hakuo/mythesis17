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
    bool init(int portno, int listen_num);
    void run();
    void stop();

private:
    TcpSocket::request_t mState;
    TcpSocket::file_info_t mFileInfo;
    std::string mFilePath;
    void closeSock(int &sockfd);
    uint8_t* handleMessage(const TcpSocket::tcp_pkg_t* package);
    uint8_t* startDownload(const uint8_t* data);
    uint8_t* transferFile(const uint8_t* data);
    uint8_t* endDownload();
    uint8_t* allocResponse(TcpSocket::request_t cmd, TcpSocket::response_t error_code, uint8_t* data = NULL, uint16_t len = 0);
    bool checkAvailableToWrite(uint32_t file_size);
    bool writeFileToMemory(const uint8_t *data);
    uint32_t calcFileCRC(const std::string filepath);

    bool sendToClient(int client_sock, char* data, uint16_t len);
    uint16_t recvFromClient(int client_sock, char* data);

    bool sendFile(int client_sock, const std::string filepath);
    bool recvFile(int client_sock, const std::string filepath);


};

#endif // TCPSERVER_H
