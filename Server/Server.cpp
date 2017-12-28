#include "headersS/Server.h"
#define MAX_CONNECTED_CLIENTS 10
#define ERROR 0

/*
 * a constructor for Server
 */
Server::Server(int port): port(port), serverSocket(0),stringSize(0) {
	cout << "Server innitialized" << endl;
}

/*
 * a constructor for Server
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
			throw "Error on accept client";
		}
		cout << "Client connected" << endl;
		close(clientSocket);
	}
}

void Server::handleClient(int clientSocket) {
	while(true) {
		//get a move from first client
		if(!getMessage(clientSocket)) {
			cout << "Error reading from client" << endl;
			return;
		}
	}
}

int Server::getMessage(int clientSocket) {
	int n = read(clientSocket, &stringSize, sizeof(stringSize));
	if(n <= 0) {
		return ERROR;
	}
	char* test = new char(stringSize);
	n = read(clientSocket, test, sizeof(char) * stringSize);
	delete test;
	return 1;
}

void Server::stop() {
	close(serverSocket);
}

