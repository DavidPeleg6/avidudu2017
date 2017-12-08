/*
 * Server.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: david
 */
#include "Server.h"

#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port): port(port), serverSocket(0) {
	cout << "Server innitialized" << endl;
}

void Server::start() {
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSocket == -1) {
		throw "Error opening socket";
	}
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
		cout << "Client connected" << endl;
		if(clientSocket == -1)
			throw "Error on accept";
		handleClient(clientSocket);
		// Close communication with the client
		close(clientSocket);
	}
}

// Handle requests from a specific client
void Server::handleClient(int clientSocket) {
	int move[2];

	while(true) {
		// Read new exercise arguments
		int n = read(clientSocket, &move[0], sizeof(move[0]));
		if (n == -1) {
			cout << "error reading Y coordinate" << endl;
		}
		if (n == 0) {
			cout <<
		}
	}
}

