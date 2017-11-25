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

/*
 * @function: initClient
 * @brief: initialize an IPC Socket client and connect to an IPC server
 * @parameter1: sock => client socket
 * @parameter2: sockpath => path to socket file on hard disk
 * @return: SUCCESS/FAIL
 */
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
                perror("ERROR on IPC_CLIENT: Connect to server failed");
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

int TCP_Socket::initServer(int& sock, int portno, int numOfClient) {
    int ret;
    struct sockaddr_in sock_addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock != FAIL) {
        bzero((char *) &sock_addr, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_addr.s_addr = INADDR_ANY;
        sock_addr.sin_port = htons(portno);
        if(bind(sock, (struct sockaddr*) &sock_addr, sizeof(sock_addr)) != FAIL) {
            if(listen(sock, numOfClient) != FAIL) {
                cout << "TCP_SERVER: Initialize successful. Ready to connect." << endl;
                ret = SUCCESS;
            }
            else {
                perror("ERROR on TCP_SERVER: Listen to socket failed");
                ret = FAIL;
            }
        }
        else {
            perror("ERROR on TCP_SERVER: Bind socket failed");
            ret = FAIL;
        }
    }
    else {
        perror("ERROR on TCP_SERVER: Create socket failed");
        ret = FAIL;
    }
    return ret;
}

int TCP_Socket::initClient(int& sock, const char* ip_addr, int portno) {
    int ret;
    struct hostent *server;
    struct sockaddr_in serv_addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock != FAIL) {
        server = gethostbyname(ip_addr);
        if(server != NULL) {
            bzero((char *) &serv_addr, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
            serv_addr.sin_port = htons(portno);
            if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) != FAIL) {
                cout << "TCP_CLIENT: A connection to server is established" << endl;
                ret = SUCCESS;
            }
            else {
                perror("ERROR on TCP_CLIENT: Connect to server failed");
                ret = FAIL;
            }
        }
        else {
            cout << "ERROR on TCP_CLIENT: Invalid IP Address" << endl;
            ret = FAIL;
        }
    }
    else {
        perror("ERROR on TCP_CLIENT: Create socket failed");
        ret = FAIL;
    }
    return ret;
}

int TCP_Socket::acceptClient(int& sockServer, int& sockClient) {
    struct sockaddr_in client_addr;
    int socklen = sizeof(struct sockaddr_in);
    sockClient = accept(sockServer, (struct sockaddr*) &client_addr, (socklen_t *) &socklen);
    return ((sockClient == FAIL)? FAIL: SUCCESS);
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
