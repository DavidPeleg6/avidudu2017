/*
 * Server.h
 *
 *  Created on: Dec 8, 2017
 *      Author: david
 */

#ifndef HEADERS_SERVER_H_
#define HEADERS_SERVER_H_
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;

class Server {
public:
	Server(int port);
	void start();
	void stop();

private:
	int port;
	int serverSocket;

	void handleClient(int clientSocket);
	int* passMove(int moveX, int moveY);
};



#endif /* HEADERS_SERVER_H_ */
