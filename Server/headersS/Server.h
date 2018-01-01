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
#include <stdlib.h>
#include <pthread.h>
#include <cstdlib>
#include "CommandManager.h"
#include "Command.h"
#define ERROR 0
#define SUCCESS 1

using namespace std;

class Server {
public:
	Server(int port, CommandManager* manager);
	void start();
	void stop();
private:
	int port;
	int serverSocket;
	CommandManager* manager;
	SocketHandler *handler;
	static pthread_mutex_t serverLock;
};

#endif /* HEADERSS_SERVER_H_ */
