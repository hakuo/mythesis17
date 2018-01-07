#include "TcpServer_Task.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

TcpServerTask::TcpServerTask()
{
    TCP_SYS_ROOT = std::string(getenv("TOOL_SYS_ROOT"));
    mServerSock = -1;
    mQueue.txQueue = -1;
    mQueue.rxQueue = -1;
    mListenNum = -1;
    mListenPort = -1;
    remain_size = 0;

}

TcpServerTask::~TcpServerTask()
{
    this->stop();
}

bool TcpServerTask::readyToRun()
{
    mQueue.txQueue = openTxQueue(OCR_QUEUE);
    mState = TcpUtils::START_DOWNLOAD;
    return (mListenNum != -1) && (mListenPort != -1)
            && (mQueue.txQueue != -1) && (initSock(mListenPort, mListenNum));
}

void TcpServerTask::setListenPort(int portno)
{
    mListenPort = portno;
}

void TcpServerTask::setListenNum(int num)
{
    mListenNum = num;
}

bool TcpServerTask::initSock(uint16_t portno, uint8_t listen_num)
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
//        mTerminate = false; // ready to listen this port
        return true;
    }
    else
    {
        std::cout << "Server already create !" << std::endl;
        return false;
    }
}

void TcpServerTask::closeSock(int &sockfd)
{
    std::cout << "Closed socket " << (int)sockfd << std::endl;
    close(sockfd);
    sockfd = -1;
}

void TcpServerTask::handleMessage(const TcpUtils::tcp_pkg_t *rxPackge, TcpUtils::tcp_pkg_t *txPackage)
{
    switch (rxPackge->header.cmd) {
    case TcpUtils::START_DOWNLOAD:
        startDownload(rxPackge->data, txPackage);
        break;
    case TcpUtils::TRANFER_FILE:
        transferFile(rxPackge->data, txPackage);
        break;
    case TcpUtils::END_DOWNLOAD:
        endDownload(txPackage);
        break;
    default:
        break;
    }
}

void TcpServerTask::startDownload(const uint8_t *data, TcpUtils::tcp_pkg_t *txPackage)
{
    std::cout << "Start Download" << std::endl;
    TcpUtils::request_t cmd = TcpUtils::START_DOWNLOAD;
    std::string tmp_dir = TCP_SYS_ROOT + TMP_PATH;
    TcpUtils::response_t error_code;
    switch (mState) {
    case TcpUtils::START_DOWNLOAD:
        memset(&mFile, 0, sizeof(mFile));
        memcpy(&mFile.header, data, sizeof(mFile.header));
        std::cout << "file_type: " << (int)mFile.header.type << std::endl;
        std::cout << "file_size: " << (int)mFile.header.size << std::endl;
        std::cout << "file_crc: " << (int)mFile.header.crc << std::endl;
        std::cout << "from: " << mFile.header.from << std::endl;
        TcpUtils::genFilePath(mFile, tmp_dir.c_str());
        if(TcpUtils::checkAvailableToWrite(mFile))
        {
            remain_size = mFile.header.size;
            error_code = TcpUtils::POSITIVE_RESPONSE;
            mState = TcpUtils::TRANFER_FILE;
        }
        else
        {
            // File too large, don't have enough memory
            error_code = TcpUtils::NEGATIVE_RESPONSE_NOTSEND;
        }
        break;
    case TcpUtils::TRANFER_FILE:
        // fall-through
    case TcpUtils::END_DOWNLOAD: // Never turn to this state
        // fall-through
    default:
        error_code = TcpUtils::NEGATIVE_RESPONSE_RESEND;
        break;
    }
    TcpUtils::makeTxPackage(txPackage, cmd, error_code);
}

void TcpServerTask::transferFile(const uint8_t *data, TcpUtils::tcp_pkg_t *txPackage)
{
    std::cout << "tranfer file" << std::endl;
    TcpUtils::request_t cmd = TcpUtils::TRANFER_FILE;
    TcpUtils::response_t error_code;
    uint32_t writelen = (remain_size > DATA_SIZE) ? DATA_SIZE : remain_size;
    switch (mState) {
    case TcpUtils::TRANFER_FILE:
        if(TcpUtils::writeFileToMemory(mFile.filepath, data, writelen))
        {
            remain_size -= writelen;
            error_code = TcpUtils::POSITIVE_RESPONSE;
        }
        else
        {
            error_code = TcpUtils::NEGATIVE_RESPONSE_RESEND;    // recheck ???
        }
        // don't change state
        break;
    case TcpUtils::START_DOWNLOAD:
        // fall-through
    case TcpUtils::END_DOWNLOAD: // Never turn to this state
        // fall-through
    default:
        error_code = TcpUtils::NEGATIVE_RESPONSE_NOTSEND; // Critical error
        break;
    }
    TcpUtils::makeTxPackage(txPackage, cmd, error_code);
}

void TcpServerTask::endDownload(TcpUtils::tcp_pkg_t *txPackage)
{
    std::cout << "end Download" << std::endl;
    TcpUtils::response_t error_code;
    TcpUtils::request_t cmd = TcpUtils::END_DOWNLOAD;
    switch (mState) {
    case TcpUtils::TRANFER_FILE:
        if(TcpUtils::verifyDownloadPackage(mFile))
        {
            error_code = TcpUtils::POSITIVE_RESPONSE;
            notifyFileAvailable(mFile);
        }
        else
        {
            //buffer = TcpUtils::allocResponse(cmd, TcpUtils::NEGATIVE_RESPONSE_RESEND);
            error_code = TcpUtils::NEGATIVE_RESPONSE_RESEND_ALL;
            std::cout << "Download file " << mFile.filepath.c_str() << " error. Need to download again" << std::endl;
        }
        // Change state to start download again
        mState = TcpUtils::START_DOWNLOAD;
        break;
    case TcpUtils::START_DOWNLOAD:
        // fall-through
    case TcpUtils::END_DOWNLOAD: // Never turn to this state
        // fall-through
    default:
        //buffer = TcpUtils::allocResponse(cmd, TcpUtils::NEGATIVE_RESPONSE_RESEND);
        error_code = TcpUtils::NEGATIVE_RESPONSE_NOTSEND; // Critical error ???
        break;
    }
    TcpUtils::makeTxPackage(txPackage, cmd, error_code);
}

void TcpServerTask::notifyFileAvailable(const TcpUtils::file_t file)
{
    // TODO: pushTxQueue
    std::cout << "File  " << file.filepath << " download successful" << std::endl;
    if(mQueue.txQueue != -1)
    {
        message_t msg;
        memset(&msg, 0, sizeof(msg));
        memcpy(msg.msg_id, file.header.from, MSG_ID_LENGTH);
        strncpy((char *)msg.data, file.filepath.c_str(), file.filepath.length());
        pushMessageQueue(mQueue.txQueue, (char *)&msg, sizeof(msg));
        std::cout << "push a queue to OCR" << std::endl;
    }
}

void TcpServerTask::ThreadLoop()
{
    this->TaskHandler();
}

void TcpServerTask::TaskHandler()
{
    //if(mServerSock == -1) return;

    int rc, nfds, current_size;
    bool close_connect, compress_array = false;
    int client_sock = -1;
    // Initialize the timeout to 3 minutes. If no activity after 3 minutes,
    // the program will end. Timeout value is based on miliseconds.
    uint32_t timeout = 10; // poll 10ms

    // Initialize the folling structure
    struct pollfd fds[100];
    memset(fds, 0, sizeof(fds));
    nfds = 1;

    // Register server socket in polling structure
    fds[0].fd = mServerSock;
    fds[0].events = POLLIN;

    while(!mThreadTerminate)
    {
        // Call poll() and wait 3 minutes for it complete.
        std::cout << "Waiting on poll() ..." << std::endl;
        rc = poll(fds, nfds, timeout);
        // Check error for poll()
        if(rc < 0)
        {
            perror("poll() failed");
            mThreadTerminate = true;
            continue;
        }
        if(rc == 0)
        {
            //std::cout << "poll() timed out. " << std::endl;
            //mThreadTerminate = true;
            continue;
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
                mThreadTerminate = true;
                //stop(); // end_server
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
                            mThreadTerminate = true;
                            //stop(); // end_server
                        }
                        break; // continue to accept if error_type is EWOULDBLOCK
                    }

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
                TcpUtils::tcp_pkg_t *rxBuffer = NULL;  // request buffer
                TcpUtils::tcp_pkg_t *txBuffer = NULL;  // response buffer
                // Receive all incoming data on this socket before we loop back and
                // call poll again
                do
                {
                    // Receive data on this connection until the recv fails with EWOULDBLOCK
                    // If any other failure occurs, we will close the connection
                    if(rxBuffer == NULL)
                    {
                        rxBuffer = new TcpUtils::tcp_pkg_t;
                    }

                    rc = -1;
                    if(rxBuffer != NULL)
                    {
                        memset(rxBuffer, 0, sizeof(TcpUtils::tcp_pkg_t));
                        rc = recv(fds[i].fd, rxBuffer, TCP_BUFFER_SIZE, 0);
                    }

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


                    if(txBuffer == NULL)
                    {
                        txBuffer = new TcpUtils::tcp_pkg_t;
                    }

                    // Handle data and send response to client
                    handleMessage(rxBuffer, txBuffer);
                    rc = -1;
                    if(txBuffer != NULL)
                    {
                        rc = send(fds[i].fd, txBuffer, TCP_BUFFER_SIZE, 0);
                    }

                    if(rc < 0)
                    {
                        perror("send() failed");
                        close_connect = true;
                        break;
                    }
                    // Send success => receive again, if timeout, normal break
                }while(true);

                TcpUtils::freePointer(txBuffer);
                TcpUtils::freePointer(rxBuffer);

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
    }// End of server

    // Clean up all of sockets which are opening
    for(int i=0; i<nfds; ++i)
    {
        closeSock(fds[i].fd);
    }
    closeSock(mServerSock);
}

















