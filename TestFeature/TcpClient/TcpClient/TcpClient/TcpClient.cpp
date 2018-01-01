#include "TcpClient.h"
#include "TcpUtils/TcpUtils.h"
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/poll.h>
#include <sys/sendfile.h>
#include <fstream>

#define MAX_TIMEOUT_OCCUR 5
#define TIMEOUT 10
TcpClient::TcpClient()
{
    mClientSock = -1;
    mInterface = "";
}

TcpClient::~TcpClient()
{
    closeSock(mClientSock);
}

void TcpClient::setDefaultInterface(std::string interface)
{
    mInterface = interface;
}

bool TcpClient::connectToServer(const char *serv_addr_str, uint16_t portno)
{
    // check valid input
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if(serv_addr_str == NULL || (server = gethostbyname(serv_addr_str)) == NULL)
    {
        std::cout << "serv_addr_str is invalid" << std::endl;
        return false;
    }

    // create client socket
    if(mClientSock >= 0)
    {
        std::cout << "client_socket already created" << std::endl;
        return false;
    }

    mClientSock = socket(AF_INET, SOCK_STREAM, 0);
    if(mClientSock < 0)
    {
        std::cout << "create client_socket failed" << std::endl;
        return false;
    }

    // set timeout
    struct timeval tv;
    tv.tv_sec = TIMEOUT;     // 30s timeout
    tv.tv_usec = 0;
    setsockopt(mClientSock, SOL_SOCKET, SO_RCVTIMEO,
               (const char*)&tv,sizeof(struct timeval));

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    // Now connect to server
    if(connect(mClientSock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "connect to server failed" << std::endl;
        closeSock(mClientSock);
        return false;
    }

    // TODO: call recv to recieve client_id

    return true;
}

bool TcpClient::sendFile(const std::string filepath)
{
    if(mClientSock < 0)
    {
        std::cout << "Send file error. Please connect to server first" << std::endl;
        return false;
    }

    TcpUtils::request_t cmd;
    TcpUtils::response_t cmd_type = TcpUtils::REQUEST;
    size_t szLen;
    ssize_t szRecv;
    // Step 1: check file available
    if(!TcpUtils::checkFileAvailable(filepath, &szLen))
    {
        std::cout << "File not exist. Can't send this file to server" << std::endl;
        return false;
    }

    // Step 2: send file_info package: file_type, file_size, file_crc;
    TcpUtils::file_info_t file_info;
    file_info.crc = TcpUtils::calcFileCRC(filepath);
    file_info.size = szLen;
    file_info.type = TcpUtils::getFileType(filepath);
    file_info.from = TcpUtils::getIp(TCP_INTERFACE);

    TcpUtils::tcp_pkg_t *txBuffer = new TcpUtils::tcp_pkg_t;
    TcpUtils::tcp_pkg_t *rxBuffer = new TcpUtils::tcp_pkg_t;

    cmd = TcpUtils::START_DOWNLOAD;
    TcpUtils::makeTxPackage(txBuffer, cmd, cmd_type, (uint8_t *)&file_info, sizeof(file_info));


    // send until receive positive response
    if (TcpUtils::sendPackage(mClientSock, txBuffer, rxBuffer, &szRecv) == false)
    {
        TcpUtils::freePointer(txBuffer);
        TcpUtils::freePointer(rxBuffer);
        return false;
    }

    // Step 3: transfer file
    cmd = TcpUtils::TRANFER_FILE;
    std::ifstream inFile;
    uint8_t data[DATA_SIZE] = {0};
    inFile.open(filepath, std::ios::in | std::ios::binary);
    if(inFile.is_open())
    {
        while(!inFile.eof())
        {
            memset(data, 0, DATA_SIZE);
            inFile.read((char *)data, DATA_SIZE);
            TcpUtils::makeTxPackage(txBuffer, cmd, cmd_type, data, DATA_SIZE);
            if (TcpUtils::sendPackage(mClientSock, txBuffer, rxBuffer, &szRecv) == false)
            {
                TcpUtils::freePointer(txBuffer);
                TcpUtils::freePointer(rxBuffer);
                return false;
            }
        }
        inFile.close();
    }

    // Step 4: end download
    cmd = TcpUtils::END_DOWNLOAD;
    TcpUtils::makeTxPackage(txBuffer, cmd, cmd_type, data, DATA_SIZE);
    if (TcpUtils::sendPackage(mClientSock, txBuffer, rxBuffer, &szRecv) == false)
    {
        TcpUtils::freePointer(txBuffer);
        TcpUtils::freePointer(rxBuffer);
        return false;
    }

    TcpUtils::freePointer(txBuffer);
    TcpUtils::freePointer(rxBuffer);
    return true;
}


void TcpClient::closeSock(int &sockfd)
{
    if(sockfd >= 0)
    {
        close(sockfd);
        sockfd = -1;
    }
}


void TcpClient::closeSock()
{
    closeSock(mClientSock);
}



















