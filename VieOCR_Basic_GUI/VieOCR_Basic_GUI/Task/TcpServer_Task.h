#ifndef TCPSERVERTASK_H
#define TCPSERVERTASK_H

#include "TaskThread.h"
#include "TCP/TcpUtils/TcpUtils.h"

class TcpServerTask: public TaskThread
{
public:
    TcpServerTask();
    virtual ~TcpServerTask();

    void setListenPort(int portno);
    void setListenNum(int num);
    std::map<int, TcpUtils::sock_info_t> sock_map;
private:
    virtual bool readyToRun();
    virtual void TaskHandler();
    virtual void ThreadLoop();  // override

    bool initSock(uint16_t portno, uint8_t listen_num);
    void closeSock(int &sockfd);
    void handleMessage(int sock, const TcpUtils::tcp_pkg_t *rxPackge, TcpUtils::tcp_pkg_t *txPackge);
    void startDownload(int sock, const uint8_t *data, TcpUtils::tcp_pkg_t *txPackage);
    void transferFile(const uint8_t *data, TcpUtils::tcp_pkg_t *txPackage);
    void endDownload(TcpUtils::tcp_pkg_t *txPackage);
    void notifyFileAvailable(const std::string filepath);
    int mServerSock;
    int mListenPort;
    int mListenNum;
    TcpUtils::request_t mState;
    TcpUtils::file_t mFile;

};

#endif // TCPSERVERTASK_H
