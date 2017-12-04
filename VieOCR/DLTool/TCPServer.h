/*
 * TCPServer.h
 *
 *  Created on: Nov 30, 2017
 *      Author: cuongdh8
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_
#include "TCPHeader.h"
#include "../Thread/Thread.h"


#define PORT 5000
#define BACKLOG 10
#define BUFFER_LENGTH 1024

class TCPServer: public Thread {
public:
    TCPServer();
    virtual ~TCPServer();

private:
    int mSockfd;
    virtual bool readyToRun();
    virtual void threadLoop();
    bool init();
};

#endif /* TCPSERVER_H_ */
