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
#include "CommandManager.h"

using namespace std;

class Server {
public:
	Server(int port, CommandManager manager);
	void start();
	void stop();
	void handleClient(int clientSocket);
	int getString(int clientSocket);
	int passString(int clientSocket, int stringSize, char* message);
	int passInt(int clientSocket, int num);
	void closeSocket(int clientSocket);

private:
	int port;
	int serverSocket;
	CommandManager command;
};



#endif /* HEADERSS_SERVER_H_ */
