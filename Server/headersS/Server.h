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

class CommandManager;

class Server {
public:
	Server(int port);
	void start();
	void stop();
	void handleClient(int clientSocket);
	int getString(int clientSocket);
	int passString(int clientSocket, int stringSize, char* message);
	int passInt(int clientSocket, int num);
	void closeSocket(int clientSocket);
	void setCommandManager(CommandManager *manager);

private:
	int port;
	int serverSocket;
	CommandManager *manager;
};



#endif /* HEADERSS_SERVER_H_ */
