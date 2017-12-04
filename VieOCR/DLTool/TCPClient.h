/*
 * TCPClient.h
 *
 *  Created on: Dec 1, 2017
 *      Author: cuongdh8
 */

#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

#include "TCPHeader.h"

class TCPClient {
public:
    TCPClient();
    virtual ~TCPClient();

private:
    int mSockfd;
    bool init();
};

#endif /* TCPCLIENT_H_ */
