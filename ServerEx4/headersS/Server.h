/*
 * Server.h
 */

#ifndef HEADERSS_SERVER_H_
#define HEADERSS_SERVER_H_
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <cstdlib>

using namespace std;

struct Games {
	int status;
	pthread_t game_thread;
	string name;
} Games;

class Server {
public:
	Server(int port);
	void start();
	void stop();
	vector<string> getGames();

private:
	int port;
	int serverSocket;
	vector<string> games;
	int serverStatus;

	void* manageServer(void *none);
	void handleClients(int client1Socket, int client2Socket);
	int startGame(int client1Socket, int client2Socket);
	int getMove(int clientSocket, int *move);
	int passMove(int clientSocket, int *move);
};



#endif /* HEADERSS_SERVER_H_ */
