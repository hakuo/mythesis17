///*
// * socket.h
// *
// *  Created on: Nov 25, 2017
// *      Author: cuongdh8
// */
//
//#ifndef SOCKET_H_
//#define SOCKET_H_
//
//#include "../common.h"
//#include <sys/socket.h>
//#include <sys/un.h>
//#include <netdb.h>
//#include <netinet/in.h>
//#include <unistd.h>
//
//namespace IPC_Socket {
//    int initServer(int& sock, int client_sock[], const char* sockpath, int numOfClient);
//    int initClient(int& sock, const char* sockpath);
//}
//
//namespace TCP_Socket {
//    int initServer(int& sock, int portno, int numOfClient);
//    int initClient(int& sock, const char* ip_addr, int portno);
//    int acceptClient(int& sockServer, int& sockClient);
//}
//
//int readSocket(int sock, char* buffer, size_t size);
//int writeSocket(int sock, const char* buffer, size_t size);
//
//
//
//#endif /* SOCKET_H_ */
