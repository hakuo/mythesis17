/*
 * socket.cpp
 *
 *  Created on: Nov 25, 2017
 *      Author: cuongdh8
 */
#include "socket.h"

/*
 * @function: initServer
 * @brief: initialize an IPC Socket server and accept connection from clients
 * @parameter1: sock => server socket
 * @parameter2: client_sock => an array point to client sockets
 * @parameter3: sockpath => path to socket file on hard disk
 * @parameter4: numOfClient => maximum client
 * @return: SUCCESS/FAIL
 * @Note: The order of connection from clients
 */
int IPC_Socket::initServer(int& sock, int client_sock[], const char* sockpath, int numOfClient) {
    int ret;
    struct sockaddr_un sock_addr, client_addr;
    int socklen = sizeof(struct sockaddr_un);
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock != FAIL) {
        sock_addr.sun_family = AF_UNIX;
        if(sockpath != NULL) {
            strcpy(sock_addr.sun_path, sockpath);
            unlink(sockpath);
            if(bind(sock, (struct sockaddr*) &sock_addr, sizeof(sock_addr)) != FAIL) {
                if(listen(sock, numOfClient) != FAIL) {
                    ret = SUCCESS;
                    for(int i=0; i<numOfClient; ++i) {
                        // TODO Debug about client sockets
                        client_sock[i] = accept(sock, (struct sockaddr*) &client_addr, (socklen_t *) &socklen);
                        if(client_sock[i] == FAIL) {
                            perror("ERROR on IPC_SERVER: accept socket failed");
                            ret = FAIL;
                            break;
                        }
                    }
                }
                else {
                    perror("ERROR on IPC_SERVER: Listen to socket failed");
                    ret = FAIL;
                }
            }
            else {
                perror("ERROR on IPC_SERVER: Bind socket failed");
                ret = FAIL;
            }
        }
        else {
            cout << "ERROR on IPC_SERVER: Path is NULL" << endl;
            ret = FAIL;
        }
    }
    else {
        perror("ERROR on IPC_SERVER: Create socket failed");
        ret = FAIL;
    }
    return ret;
}

int IPC_Socket::initClient(int& sock, const char* sockpath) {
    int ret;
    struct sockaddr_un client_addr;
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock != FAIL) {
        client_addr.sun_family = AF_UNIX;
        if(sockpath != NULL) {
            strcpy(client_addr.sun_path, sockpath);
            if(connect(sock, (const sockaddr *) &client_addr, sizeof(client_addr)) != FAIL) {
                cout << "IPC_CLIENT: A connection to server is established" << endl;
                ret = SUCCESS;
            }
            else {
                perror("ERROR on IPC_CLIENT: connect to server failed");
                ret = FAIL;
            }
        }
        else {
            cout << "ERROR on IPC_CLIENT: Path is NULL" << endl;
            ret = FAIL;
        }
    }
    else {
        perror("ERROR on IPC_CLIENT: Create socket failed");
        ret = FAIL;
    }
    return ret;
}

int TCP_Socket::initServer(int& sock) {
    int ret;
    return ret;
}

int TCP_Socket::initClient(int& sock) {
    int ret;
    return ret;
}

int readSocket(int sock, char* buffer, size_t size) {
    int ret;
    if(read(sock, buffer, size) > 0) {
        ret = SUCCESS;
    }
    else {
        ret = FAIL;
    }
    return ret;
}

int writeSocket(int sock, const char* buffer, size_t size) {
    int ret;
    if(write(sock, buffer, size) > 0) {
        ret = SUCCESS;
    }
    else {
        ret = FAIL;
    }
    return ret;
}
