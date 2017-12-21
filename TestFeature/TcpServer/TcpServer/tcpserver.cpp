#include "tcpserver.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

////////////////////////////// TcpServer ////////////////////////////////
TcpServer::TcpServer()
{
    mServerSock = -1;
    mTerminate = false;
}

TcpServer::~TcpServer()
{

}

bool TcpServer::init(int portno, int listen_num)
{
    int rc, on = 1;
    struct sockaddr_in serv_addr;
    if(mServerSock == -1)
    {
        mServerSock = socket(AF_INET, SOCK_STREAM, 0);
        if(mServerSock < 0)
        {
            perror("Open socket failed");
            return false;
        }

        // Allow socket descriptor to be reuseable
        rc = setsockopt(mServerSock, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
        if(rc < 0)
        {
            perror("setsockopt() failed");
            closeSock(mServerSock);
            return false;
        }

        // Set socket to be nonblocking. All of sockets for the incoming connections
        // will also be nonblocking since they will inherit that state from server
        // socket
        rc = ioctl(mServerSock, FIONBIO, (char *)&on);
        if(rc < 0)
        {
            perror("ioctl() failed");
            closeSock(mServerSock);
            return false;
        }

        // Bind socket
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(portno);
        rc = bind(mServerSock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if(rc < 0)
        {
            perror("Bind socket failed");
            closeSock(mServerSock);
            return false;
        }

        // Set listen backlog
        rc = listen(mServerSock, listen_num);
        if(rc < 0)
        {
            perror("listen() failed");
            closeSock(mServerSock);
            return false;
        }
        std::cout << "Initialize TcpServer successful" << std::endl;
        std::cout << "Listening port " << (int)portno << std::endl;
        return true;
    }
    else
    {
        std::cout << "Server already create !" << std::endl;
        return false;
    }
}

void TcpServer::run()
{
    if(mServerSock == -1) return;

    int rc, nfds, current_size;
    bool close_connect, compress_array = false;
    int client_sock = -1;
    // Initialize the timeout to 3 minutes. If no activity after 3 minutes,
    // the program will end. Timeout value is based on miliseconds.
    uint32_t timeout = 3*60*1000;

    // Initialize the folling structure
    struct pollfd fds[100];
    memset(fds, 0, sizeof(fds));
    nfds = 1;

    // Register server socket in polling structure
    fds[0].fd = mServerSock;
    fds[0].events = POLLIN;

    do
    {
        // Call poll() and wait 3 minutes for it complete.
        std::cout << "Waiting on poll() ..." << std::endl;
        rc = poll(fds, nfds, timeout);

        // Check error for poll()
        if(rc < 0)
        {
            perror("poll() failed");
            break;
        }
        if(rc == 0)
        {
            std::cout << "poll() timed out. End program" << std::endl;
            break;
        }

        // One or more descriptors are readable. Need to determine which ones they are
        current_size = nfds;
        for(int i=0; i<current_size; ++i)
        {
            // Loop through to find the descriptors that returned POLLIN and determine
            // whether it's the listening or the active connection.
            if(fds[i].revents == 0) continue;

            // If reevents is not POLLIN. It's an unexpected result.
            // Log and end the server
            if(fds[i].revents != POLLIN)
            {
                std::cout << "Error! revents = " << (int)fds[i].revents << std::endl;
                stop(); // end_server
                break;
            }
            if(fds[i].fd == mServerSock)
            {
                std::cout << "server_sock is readable" << std::endl;
                // Accept all incoming connections that are queued up on the listening
                // socket before we loop back and call poll() again.
                do
                {
                    client_sock = accept(mServerSock, NULL, NULL);
                    if(client_sock < 0)
                    {
                        if(errno != EWOULDBLOCK)
                        {
                            perror("accept() failed");
                            stop(); // end_server
                        }
                        break; // continue to accept if error_type is EWOULDBLOCK
                    }

                    // Add new incoming connection to the pollfd structure
                    std::cout << "New incoming connection - " << (int)client_sock << std::endl;
                    fds[nfds].fd = client_sock;
                    fds[nfds].events = POLLIN;
                    ++nfds;

                    // Loop back to accept another incoming connection
                }while(client_sock != -1);
            }
            else
            {
                // A client_sock is readable
                std::cout << "client_sock " << (int)fds[i].fd << " is readable" << std::endl;
                close_connect = false;
                uint8_t* rxBuffer = NULL;  // request buffer
                uint8_t* txBuffer = NULL;  // response buffer
                // Receive all incoming data on this socket before we loop back and
                // call poll again
                do
                {
                    // Receive data on this connection until the recv fails with EWOULDBLOCK
                    // If any other failure occurs, we will close the connection
                    rxBuffer = (uint8_t *) calloc(BUFFER_SIZE, 1);
                    rc = recv(fds[i].fd, rxBuffer, sizeof(rxBuffer), 0);
                    if(rc < 0)
                    {
                        if(errno != EWOULDBLOCK)
                        {
                            perror("recv() failed");
                            close_connect = true;
                        }
                        break;
                    }

                    // Check connection closed by client
                    if(rc == 0)
                    {
                        std::cout << "Connection closed" << std::endl;
                        close_connect = true;
                        break;
                    }

                    // Data arrived
                    std::cout << (int)rc << " bytes received" << std::endl;

                    // Handle data and send response to client
                    txBuffer = handleMessage((TcpSocket::tcp_pkg_t*)rxBuffer);
                    rc = send(fds[i].fd, txBuffer, sizeof(txBuffer), 0);
                    if(rc < 0)
                    {
                        perror("send() failed");
                        close_connect = true;
                        break;
                    }
                    if(rxBuffer != NULL)
                    {
                        free(rxBuffer);
                        rxBuffer = NULL;
                    }
                    if(txBuffer != NULL)
                    {
                        free(rxBuffer);
                        rxBuffer = NULL;
                    }
                }while(true);

                // If close_connect flag was turned on, we need to clean up this active
                // connection. This clean up process includes removing the descriptor
                if(close_connect)
                {
                    closeSock(fds[i].fd);
                    compress_array = true;
                }
            } // end of existing connection is readable
        } // end of loop through pollable descriptors

        // If the compress_array flag was turned on, we need to squeeze together the array
        // and decrement the number of file descriptors. We don't need to move back the
        // events and revents fields because the events will always be POLLIN in this case,
        // and revents is output.
        if(compress_array)
        {
            compress_array = false;
            for(int i=0; i<nfds; ++i)
            {
                if(fds[i].fd == -1)
                {
                    for(int j=i; j<nfds; ++j)
                    {
                        fds[j].fd = fds[j+1].fd;
                    }
                    --nfds;
                }
            }
        }
    } while(!mTerminate); // End of server

    // Clean up all of sockets which are opening
    for(int i=0; i<nfds; ++i)
    {
        closeSock(fds[i].fd);
    }
    closeSock(mServerSock);
}

void TcpServer::stop()
{
    mTerminate = true;
}

void TcpServer::closeSock(int &sockfd)
{
    std::cout << "Closed socket " << (int)sockfd << std::endl;
    close(sockfd);
    sockfd = -1;
}

uint8_t* TcpServer::handleMessage(const TcpSocket::tcp_pkg_t *package)
{
    uint8_t* buffer = NULL;
    TcpSocket::request_t fn_type = package->header.cmd;
    switch (fn_type) {
    case TcpSocket::START_DOWNLOAD:
        buffer = startDownload(package->data);
        break;
    case TcpSocket::TRANFER_FILE:
        buffer = transferFile(package->data);
        break;
    case TcpSocket::END_DOWNLOAD:
        buffer = endDownload();
        break;
    default:
        break;
    }
    return buffer;
}

uint8_t* TcpServer::startDownload(const uint8_t *data)
{
    uint8_t* buffer;
    TcpSocket::request_t cmd = TcpSocket::START_DOWNLOAD;
    switch (mState) {
    case TcpSocket::START_DOWNLOAD:
        memcpy(&mFileInfo, data, sizeof(mFileInfo));
        std::cout << "file_type: " << (int)mFileInfo.type << std::endl;
        std::cout << "file_size: " << (int)mFileInfo.size << std::endl;
        std::cout << "file_crc: " << (int)mFileInfo.crc << std::endl;
        // TODO: checkAvailable to write
        if(checkAvailableToWrite(mFileInfo.size))
        {
            buffer = allocResponse(cmd, TcpSocket::POSITIVE_RESPONSE);
            mState = TcpSocket::TRANFER_FILE;
        }
        else
        {
            // File too large, don't have enough memory
            buffer = allocResponse(cmd, TcpSocket::NEGATIVE_RESPONSE_NOTSEND);
        }
        break;
    case TcpSocket::TRANFER_FILE:
        // fall-through
    case TcpSocket::END_DOWNLOAD: // Never turn to this state
        // fall-through
    default:
        buffer = allocResponse(cmd, TcpSocket::NEGATIVE_RESPONSE_RESEND);
        break;
    }
    return buffer;
}

uint8_t* TcpServer::transferFile(const uint8_t *data)
{
    uint8_t* buffer;
    TcpSocket::request_t cmd = TcpSocket::TRANFER_FILE;
    switch (mState) {
    case TcpSocket::TRANFER_FILE:
        // TODO: write File
        if(writeFileToMemory(data)){ buffer = allocResponse(cmd, TcpSocket::POSITIVE_RESPONSE); }
        else{ buffer = allocResponse(cmd, TcpSocket::NEGATIVE_RESPONSE_RESEND); }
        // don't change state
        break;
    case TcpSocket::START_DOWNLOAD:
        // fall-through
    case TcpSocket::END_DOWNLOAD: // Never turn to this state
        // fall-through
    default:
        buffer = allocResponse(cmd, TcpSocket::NEGATIVE_RESPONSE_RESEND);
        break;
    }
    return buffer;
}

uint8_t* TcpServer::endDownload()
{
    uint8_t* buffer;

    TcpSocket::request_t cmd = TcpSocket::END_DOWNLOAD;
    switch (mState) {
    case TcpSocket::TRANFER_FILE:
        // TODO: calcFileCRC
        if(calcFileCRC(mFilePath) == mFileInfo.crc){ buffer = allocResponse(cmd, TcpSocket::POSITIVE_RESPONSE); }
        else { buffer = allocResponse(cmd, TcpSocket::NEGATIVE_RESPONSE_RESEND); }
        // Change state to start download again
        mState = TcpSocket::START_DOWNLOAD;
        break;
    case TcpSocket::START_DOWNLOAD:
        // fall-through
    case TcpSocket::END_DOWNLOAD: // Never turn to this state
        // fall-through
    default:
        buffer = allocResponse(cmd, TcpSocket::NEGATIVE_RESPONSE_RESEND);
        break;
    }
    return buffer;
}

uint8_t* TcpServer::allocResponse(TcpSocket::request_t cmd, TcpSocket::response_t error_code, uint8_t *data, uint16_t len)
{
    TcpSocket::tcp_pkg_t* buffer = (TcpSocket::tcp_pkg_t*)calloc(BUFFER_SIZE, 1);
    buffer->header.cmd = cmd;
    buffer->header.error_code = error_code;
    if((data != NULL) && (len != 0))
    {
        memcpy(buffer->data, data, len);
    }
    return (uint8_t*)buffer;
}

bool TcpServer::checkAvailableToWrite(uint32_t file_size)
{
    return true;
}

bool TcpServer::writeFileToMemory(const uint8_t *data)
{
    return true;
}

uint32_t TcpServer::calcFileCRC(const std::string filepath)
{
    uint32_t crc = 0;
    return crc;
}
//bool TcpServer::sendFile(int client_sock, const std::string filepath)
//{
//    bool ret = false;
//    return ret;
//}

//bool TcpServer::recvFile(int client_sock, const std::string filepath)
//{
//    bool ret = false;
//    return ret;
//}

//bool TcpServer::checkAvailableToWrite(uint32_t file_size)
//{
//    bool ret = false;
//    return ret;
//}

//uint32_t TcpServer::calcFileCRC(const std::string filepath)
//{
//    uint32_t crc = 0;
//    return crc;
//}





























