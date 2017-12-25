#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <stdint.h>
#include <string>

class TcpClient
{
public:
    TcpClient();
    ~TcpClient();

    bool connectToServer(const char* serv_addr_str, uint16_t portno);
    bool sendFile(const std::string filepath);
    void closeSock(int &sockfd);
private:
    int mClientSock;

};

#endif // TCPCLIENT_H
