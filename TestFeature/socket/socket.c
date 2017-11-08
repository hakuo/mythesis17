/*
 * socket.c
 *
 *  Created on: Nov 7, 2017
 *      Author: cuongdh8
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

void *startServer(void* arg) {
	int server_sock, client_sock;
	int portno, num;
	struct sockaddr_in server_addr, client_addr;
	char buffer[256];
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(server_sock < 0) {
		perror("ERROR opening socket");
		close(server_sock);
		exit(1);
	}

	portno = 5001;
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(portno);
	if(bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		perror("ERROR on binding");
		close(server_sock);
		exit(1);
	}

	listen(server_sock, 5);

	int client_len = sizeof(client_addr);
	client_sock = accept(server_sock, (struct sockaddr *)&client_addr, (socklen_t *)&client_len);
	if(client_sock < 0) {
		perror("ERROR on accept");
		close(server_sock);
		close(client_sock);
		exit(1);
	}

	bzero(buffer, 256);
	num = read(client_sock, buffer, 255);
	if(num < 0) {
		perror("ERROR reading from socket");
		close(server_sock);
		close(client_sock);
		exit(1);
	}
	printf("Here is the message %s\n", buffer);

	num = write(client_sock, "I got your message", 18);
	if(num < 0) {
		perror("ERROR writing to socket");
		close(server_sock);
		close(client_sock);
		exit(1);
	}
	close(server_sock);
	close(client_sock);
	return NULL;
}

void *startClient(void *arg) {
	int sockfd;
	struct sockaddr_in serv_addr;
	int portno = 5001;
	int n;
	char buffer[256];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("ERROR opening socket");
		close(sockfd);
		exit(1);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR connecting");
		close(sockfd);
		exit(1);
	}

	/* Now ask for a message from the user, this message
	 * will be read by server
	 */

	char* string = "Hello World";
	memcpy(buffer, string, strlen(string)+1);

	/* Send message to the server */
	n = write(sockfd, buffer, strlen(buffer));

	if (n < 0) {
		perror("ERROR writing to socket");
		close(sockfd);
		exit(1);
	}

	/* Now read server response */
	bzero(buffer,256);
	n = read(sockfd, buffer, 255);
	if (n < 0) {
		perror("ERROR reading from socket");
		close(sockfd);
		exit(1);
	}
	printf("%s\n",buffer);
	close(sockfd);
	return NULL;
}
int main()
{
	pthread_t server_thread, client_thread;
	int ret;
	ret = pthread_create(&server_thread, NULL, &startServer, NULL);
	if(ret != 0) {
		printf("Can't create thread\n");
		return -1;
	}
	ret = pthread_create(&client_thread, NULL, &startClient, NULL);
	if(ret != 0) {
		printf("Can't create thread\n");
		return -1;
	}

	pthread_join(server_thread, NULL);
	pthread_join(client_thread, NULL);
	return 0;
}
