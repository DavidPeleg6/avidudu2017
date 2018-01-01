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
};

/*
 * a method to pass a given number to the client
 * @param clientSocket = a socket to write to (int)
 * @param num = a number to pass (int)
 * @return = int indicating success or fail
 */
int passInt(int clientSocket, int num) {
	int n = write(clientSocket, &num, sizeof(int));
	if(n <= 0) {
		throw ERROR;
	}
	return 1;
}

/*
 * a method to send a string to a given client
 * @param clientSocket = the client (int) to write to
 * @param stringSize = the size (int) of message to be sent
 * @param message = a char array to be sent
 * @return = an int indicating success or fail
 */
int passString(int clientSocket, int stringSize, const char* message) {
	int size = stringSize+1;
	int n = write(clientSocket, &size, sizeof(size));
	if(n <= 0) {
		return ERROR;
	}
	n = write(clientSocket, message, size);
	return 1;
}

/*
 * a method for getting a string input from client
 * @param clientSocket = the client (int) to read from
 * @return = a char array containing the message, NULL if fail
 */
char* getString(int clientSocket) {
	//read the size of input that will be given
	int stringSize;
	int n = read(clientSocket, &stringSize, sizeof(stringSize));
	if(n <= 0) {
		return NULL;
	}
	passInt(clientSocket, 1);
	//read a message in the given size
	char* message = new char[stringSize];
	n = read(clientSocket, message, stringSize);
	cout << message << endl;
	return message;
}




#endif /* HEADERSS_SERVER_H_ */
