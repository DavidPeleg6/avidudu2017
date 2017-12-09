/*
 * Server.cpp
 * a class representing the game server
 */
#include "headersS/Server.h"
#include <stdio.h>

#define MAX_CONNECTED_CLIENTS 10
#define CLOSED -4
#define END -2
#define ERROR 0

/*
 * a constructor for Server
 */
Server::Server(int port): port(port), serverSocket(0) {
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
	struct sockaddr_in client1Address, client2Address;
	socklen_t client1AddressLen, client2AddressLen;
	while(true) {
		cout << "Waiting for client connections..." << endl;
		// Accept a new client connection
		int client1Socket = accept(serverSocket, (struct sockaddr*)&client1Address,
				&client1AddressLen);
		if(client1Socket == -1) {
			throw "Error on accept client 1";
		}
		cout << "Client 1 connected" << endl;
		// Accept a new client connection
		int client2Socket = accept(serverSocket, (struct sockaddr*)&client2Address,
				&client2AddressLen);
		if(client2Socket == -1) {
			close(client1Socket);
			throw "Error on accept client 2";
		}
		cout << "Client 2 connected" << endl;
		//play game
		handleClients(client1Socket, client2Socket);
		// Close communication with the client
		close(client1Socket);
		close(client2Socket);
	}
}
/*
 * Manages the data transfer between two clients playing a game.
 */
void Server::handleClients(int client1Socket, int client2Socket) {
	//send a single digit to the clients (first = 1, second = 2)
	if(!startGame(client1Socket, client2Socket)) {
		return;
	}
	while(true) {
		//get a move from first client
		int n = getMove(client1Socket);
		if (n == CLOSED) {
			cout << "Client 1 disconnected" << endl;
			break;
		}
		if(n == ERROR) {
			cout << "Error reading from client 1" << endl;
			break;
		}
		cout << move[2] << " | (" << move[0] << ", " << move[1] << ")" << endl;
		//pass move to the second
		if(passMove(client2Socket) == ERROR) {
			cout << "Error writing to client 2" << endl;
			break;
		}
		//check if game is alive
		if(move[2] == END) {
			break;
		}
		//get a move from first client
		n = getMove(client2Socket);
		if (n == CLOSED) {
			cout << "Client 2 disconnected" << endl;
			break;
		}
		if(n == ERROR) {
			cout << "Error reading from client 2" << endl;
			break;
		}
		//pass move to the first
		cout << move[2] << " | (" << move[0] << ", " << move[1] << ")" << endl;
		if(passMove(client1Socket) == ERROR) {
			cout << "Error writing to client 1" << endl;
			break;
		}
		if(move[2] == END) {
			break;
		}
	}
	return;
}
/*
 * Tells each client what color they are.
 * @param clientSocket1 - the socket being used by the first client.
 * @param clientSocket2 - the socket being used by the second client.
 * @return - error code if an error happened.
 */
int Server::startGame(int client1Socket, int client2Socket) {
	int turn = 2;
	int n = write(client1Socket, &turn, sizeof(turn));
	if(n == -1) {
		cout << "Error writing to client 1" << endl;
		return ERROR;
	}
	turn--;
	n = write(client2Socket, &turn, sizeof(turn));
	if(n == -1) {
		cout << "Error writing to client 2" << endl;
		return ERROR;
	}
	return 1;
}
/*
 * Gets a move from a client.
 * @param clientSocket - the socket being used by the client in question.
 * @return - error code if an error happened.
 */
int Server::getMove(int clientSocket) {
	int n = read(clientSocket, &move[0], sizeof(move[0]));
	if(n == -1) {
		return ERROR;
	} if (n == 0) {
		return CLOSED;
	}
	n = read(clientSocket, &move[1], sizeof(move[1]));
	if(n == -1) {
		return ERROR;
	} if (n == 0) {
		return CLOSED;
	}
	n = read(clientSocket, &move[2], sizeof(move[2]));
	if(n == -1) {
		return ERROR;
	} if (n == 0) {
		return CLOSED;
	}
	return 1;
}
/*
 * Sends a move to a client.
 * @param clientSocket - the socket being used by the client in question.
 * @return - error code if an error happened.
 */
int Server::passMove(int clientSocket) {
	int n = write(clientSocket, &move[0], sizeof(move[0]));
	if(n == -1) {
		return ERROR;
	}
	n = write(clientSocket, &move[1], sizeof(move[1]));
	if(n == -1) {
		return ERROR;
	}
	n = write(clientSocket, &move[2], sizeof(move[2]));
	if(n == -1) {
		return ERROR;
	}
	return 1;
}
/*
 * Shuts the server down.
 */
void Server::stop() {
	close(serverSocket);
}
