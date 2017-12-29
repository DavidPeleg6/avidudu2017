#include "headersS/Server.h"
#include <stdlib.h>
#define MAX_CONNECTED_CLIENTS 10
#define ERROR 0

/*
 * a constructor for Server
 * @param port = a port (int) number to set up server
 * @param manager = a CommandManager class to manage server actions
 */
Server::Server(int port, CommandManager manager): port(port), serverSocket(0), manager(manager) {
	cout << "Server innitialized" << endl;
}

/*
 * a method for running the mainframe of the server
 */
void Server::start() {
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSocket == -1) {
		throw "Error opening socket";
	}
	//server socket innitialize
	struct sockaddr_in serverAddress;
	bzero((void *)&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);
	if (bind(serverSocket, (struct sockaddr*)&serverAddress,
			sizeof(serverAddress)) == - 1) {
		throw "Error on binding";
	}
	cout << "Server started" << endl;
	// Start listening to incoming connections
	listen(serverSocket, MAX_CONNECTED_CLIENTS);
	// Define the client socket's structures
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen;
	while(true) {
		cout << "Waiting for client connections..." << endl;
		// Accept a new client connection
		int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress,
				&clientAddressLen);
		if(clientSocket == -1) {
			cout << "Error on accept client" << endl;
		}
		cout << "Client connected" << endl;
		handleClient(clientSocket);
	}
}

/*
 * a method for handling all commands received from client - might become threaded later
 * @param clientSocket = the socket of the calling client
 */
void Server::handleClient(int clientSocket) {
	char* msg;
	while(true) {
		//get an input string from client
		msg = getString(clientSocket);
		if(msg == NULL) {
			cout << "Error reading from client" << endl;
			return;
		}
		//get appropriate command from the manager and execute
		Command *command = manager.getCommand(msg, clientSocket);
		command -> execute(this);
	}
}

/*
 * a method for getting a string input from client
 * @param clientSocket = the client (int) to read from
 * @return = a char array containing the message, NULL if fail
 */
char* Server::getString(int clientSocket) {
	//read the size of input that will be given
	int stringSize;
	int n = read(clientSocket, &stringSize, sizeof(stringSize));
	cout << stringSize << endl;//TODO delet
	if(n <= 0) {
		return NULL;
	}
	//read a message in the given size
	char* message = (char*)malloc(sizeof(char) * stringSize);
	n = read(clientSocket, message, stringSize);
	cout << message << endl;
	return message;
}

/*
 * a method to send a string to a given client
 * @param clientSocket = the client (int) to write to
 * @param stringSize = the size (int) of message to be sent
 * @param message = a char array to be sent
 * @return = an int indicating success or fail
 */
int Server::passString(int clientSocket, int stringSize, const char* message) {
	int n = write(clientSocket, &stringSize, sizeof(stringSize));
	if(n <= 0) {
		return ERROR;
	}
	n = write(clientSocket, message, stringSize);
	return 1;
}

/*
 * closes a given socket
 * clientSocket = (int) socket to be closed
 */
void Server::closeSocket(int clientSocket) {
	close(clientSocket);
}

/*
 * closes the server socket
 */
void Server::stop() {
	close(serverSocket);
}

/*
 * a method to pass a given number to the client
 * @param clientSocket = a socket to write to (int)
 * @param num = a number to pass (int)
 * @return = int indicating success or fail
 */
int Server::passInt(int clientSocket, int num) {
	int n = write(clientSocket, &num, sizeof(int));
	if(n <= 0) {
		return ERROR;
	}
	return 1;
}

