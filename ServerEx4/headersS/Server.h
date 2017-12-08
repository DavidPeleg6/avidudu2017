/*
 * Server.h
 *
 *  Created on: Dec 8, 2017
 *      Author: david
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
	int move[3];

	void handleClients(int client1Socket, int client2Socket);
	int startGame(int client1Socket, int client2Socket);
	int getMove(int clientSocket);
	int passMove(int clientSocket);
};



#endif /* HEADERSS_SERVER_H_ */
