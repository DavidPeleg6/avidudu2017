#include "headers/Client.h"
#include <stdlib.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
using namespace std;
/*
 * Constructor, makes a new client object.
 * @param serverIP - the IP adress of the server the client will connect to.
 * @param serverPort - the port it will use to connect to the server.
 */
Client::Client(const char *serverIP, int serverPort):
	serverIP(serverIP), serverPort(serverPort),
	clientSocket(0) {
		cout << "Client" << endl;
}
Client::~Client() {
	//free(serverIP);
	//TODO this maybe I dunno
}
/*
 * Connects to the server as the name would imply.
 * @return the color of this client.
 */
int Client::connectToServer() {
	// Create a socket point
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1) {
		throw "Error opening socket";
	}
	// Convert the ip string to a network address
	struct in_addr address;
	if (!inet_aton(serverIP, &address)) {
		throw "Can't parse IP address";
	}
	// Get a hostent structure for the given host address
	struct hostent *server;
	server = gethostbyaddr((const void *)&address, sizeof
			address, AF_INET);
	if (server == NULL) {
		throw "Host is unreachable";
	}
	// Create a structure for the server address
	struct sockaddr_in serverAddress;
	bzero((char *)&address, sizeof(address));
	serverAddress.sin_family = AF_INET;
	memcpy((char *)&serverAddress.sin_addr.s_addr, (char
			*)server->h_addr, server->h_length);
	// htons converts values between host and network byte orders
	serverAddress.sin_port = htons(serverPort);
	// Establish a connection with the TCP server
	if (connect(clientSocket, (struct sockaddr
			*)&serverAddress, sizeof(serverAddress)) == -1) {
		throw "Error connecting to server";
	}
	cout << "Connected to server" << endl;
	cout << "waiting for opponent..." << endl;
	int color;
	int n = read(clientSocket, &color, sizeof(color));
	if (n == -1) {
		throw "Error reading color from socket";
	}
	cout << "You are player number: " << color << endl;
	if (color == 1) {
		cout << "player 2 logged in" << endl;
	}
	return color;
}
/*
 * Sends a move to the other player.
 * @param x - the x coordinate
 * @param y - the y coordinate
 * @param color - the color of the player making the move.
 */
void Client::SendMove(int x, int y, int color) {
	// Write the exercise arguments to the socket
	int n = write(clientSocket, &x, sizeof(x));
	if (n == -1) {
		throw "Error writing x to socket";
	}
	n = write(clientSocket, &y, sizeof(y));
	if (n == -1) {
		throw "Error writing y to socket";
	}
	n = write(clientSocket, &color, sizeof(color));
	if (n == -1) {
		throw "Error writing color to socket";
	}
}
/*
 * Gets a move from the other player which will be acted out on this instance of the game.
 */
int* Client::GetMove() {
	int n, x, y, color;
	n = read(clientSocket, &x, sizeof(x));
	if (n == -1) {
		throw "Error reading x from socket";
	}
	n = read(clientSocket, &y, sizeof(y));
	if (n == -1) {
		throw "Error reading y from socket";
	}
	n = read(clientSocket, &color, sizeof(color));
	if (n == -1) {
		throw "Error reading color from socket";
	}
	int* move = (int*)calloc(3, sizeof(int));
	move[0] = x;
	move[1] = y;
	move[2] = color;
	return move;
}
