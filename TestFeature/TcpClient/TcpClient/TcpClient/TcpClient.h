#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <stdint.h>
#include <string>

#define TCP_INTERFACE "wlan0"
class TcpClient
{
public:
    TcpClient();
    ~TcpClient();

    void setDefaultInterface(std::string interface);
    bool connectToServer(const char* serv_addr_str, uint16_t portno);
    bool sendFile(const std::string filepath);
    void closeSock(int &sockfd);
    void closeSock();
private:
    int mClientSock;
    std::string mInterface;
};

#endif // TCPCLIENT_H
