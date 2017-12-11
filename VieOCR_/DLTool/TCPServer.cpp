/*
 * TCPServer.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: cuongdh8
 */

#include "TCPServer.h"

TCPServer::TCPServer() {
    // TODO Auto-generated constructor stub
    mSockfd = 0;
}

TCPServer::~TCPServer() {
    // TODO Auto-generated destructor stub
}

bool TCPServer::readyToRun() {
    return this->init();
}

void TCPServer::threadLoop() {
    struct sockaddr_in addr_remote;
    int sin_size, client_sock, filesize, count, filecrc;
    char filename[256];
    char buffer[BUFFER_LENGTH];
    sin_size = sizeof(addr_remote);

    while(1) {
        client_sock = accept(mSockfd, (struct sockaddr *)&addr_remote, (socklen_t *)&sin_size);
        if(client_sock == -1) {
            perror("ERROR: Obtain new Socket Descriptor error");
            continue;
        }
        cout << "[SERVER] Server has got connect from " << inet_ntoa(addr_remote.sin_addr) << endl;
        /* Child process */
        if(!fork()) {
            // TODO receive first msg: filesize, filename, filecrc


            // TODO receive file data
            count = 0;
            while(count < filesize) {
                //TODO receive socket and write to file

            }
            // TODO check CRC file
            _exit(0);
        }
    }
}

bool TCPServer::init() {
    mSockfd = socket(AF_INET, SOCK_STREAM, 0);
    char out[64] = {0};
    struct sockaddr_in addr_local;
    if(mSockfd == -1) {
        perror("ERROR: Failed to create socket descriptor");
        return false;
    }
    cout << "[SERVER] Obtain socket descriptor successfully." << endl;
    bzero(&addr_local, sizeof(addr_local));
    addr_local.sin_family = AF_INET;    //protocol family
    addr_local.sin_port = htons(PORT);  //Port number
    addr_local.sin_addr.s_addr = INADDR_ANY;

    if(bind(mSockfd, (struct sockaddr*)&addr_local, sizeof(struct sockaddr)) == -1) {
        sprintf(out, "ERROR: Failed to bind port %d", PORT);
        perror(out);
        return false;
    }
    cout << "[SERVER] Bind TCP port " << PORT << " in address " << INADDR_ANY << " successfully" << endl;

    if(listen(mSockfd, BACKLOG) == -1) {
        sprintf(out, "ERROR: Failed to listen port %d", PORT);
        perror(out);
        return false;
    }
    cout << "[SERVER] Listening TCP port " << PORT << " in address " << INADDR_ANY << endl;
    cout << "[SERVER]  Initialize TCP server successful" << endl;
    return true;

}


