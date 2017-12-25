#include "tcpclient.h"
#include "TcpUtils/TcpUtils.h"
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/poll.h>

#define MAX_TIMEOUT_OCCUR 5
#define TIMEOUT 10
TcpClient::TcpClient()
{
    mClientSock = -1;
}

TcpClient::~TcpClient()
{
    closeSock(mClientSock);
}

void TcpClient::closeSock(int &sockfd)
{
    if(sockfd >= 0)
    {
        close(sockfd);
        sockfd = -1;
    }
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

    size_t szLen;
    // Step 1: check file available
    if(!TcpUtils::checkFileAvailable(filepath, &szLen))
    {
        std::cout << "File not exist. Can't send this file to server" << std::endl;
        return false;
    }

    int rc;
    // Step 2: send file_info package: file_type, file_size, file_crc;
    TcpUtils::file_info_t file_info;
    file_info.crc = TcpUtils::calcFileCRC(filepath);
    file_info.size = szLen;
    file_info.type = TcpUtils::getFileType(filepath);

    TcpUtils::tcp_pkg_t package;
    uint8_t *txBuffer = NULL;
    uint8_t *rxBuffer = (uint8_t *)calloc(TCP_BUFFER_SIZE, 1);
    if(rxBuffer == NULL)
    {
        std::cout << "sendFile(): alloc buffer failed" << std::endl;
        return false;
    }
    txBuffer = TcpUtils::allocResponse(TcpUtils::START_DOWNLOAD, TcpUtils::REQUEST, (uint8_t *)&file_info, sizeof(file_info));
    if(txBuffer == NULL)
    {
        std::cout << "sendFile(): alloc buffer failed" << std::endl;
        free(rxBuffer);
        return false;
    }

    uint8_t isPositive = false;
    uint8_t count;
    do {
        rc = send(mClientSock, txBuffer, TCP_BUFFER_SIZE, 0);
        if(rc < 0)
        {
            std::cout << "send file_info error" << std::endl;
            free(txBuffer);
            free(rxBuffer);
            return false;
        }
        count = 0;
        do
        {
            rc = recv(mClientSock, rxBuffer, TCP_BUFFER_SIZE, 0);
            if(rc < 0)
            {
                if(errno != EWOULDBLOCK)
                {
                    std::cout << "recv() failed" << std::cout;
                    free(txBuffer);
                    free(rxBuffer);
                    return false;
                }
                count++;
                continue;
            }
            if(rc == 0)
            {
                std::cout << "Connection closed" << std::endl;
                return false;
            }

            // Response arrived
            std::cout << (int)rc << " bytes received" << std::endl;


        }while(count < MAX_TIMEOUT_OCCUR);

    } while(!isPositive);





}




















