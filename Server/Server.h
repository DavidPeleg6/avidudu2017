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
	int stringSize = 0;

	void handleClient(int clientSocket);
	int startGame(int client1Socket, int client2Socket);
	int getMessage(int clientSocket);
	int passMove(int clientSocket);
};



#endif /* HEADERSS_SERVER_H_ */
