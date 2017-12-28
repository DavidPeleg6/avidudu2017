/*
 * Server.h
 */

#ifndef HEADERSS_SERVER_H_
#define HEADERSS_SERVER_H_
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
	int stringSize;

	void handleClient(int clientSocket);
	int getMessage(int clientSocket);
	int passMove(int clientSocket);
};



#endif /* HEADERSS_SERVER_H_ */
