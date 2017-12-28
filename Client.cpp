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
/*
 * Destructor, does nothing.
 */
Client::~Client() { }
/*
 * Connects to the server as the name would imply.
 */
void Client::connectToServer() {
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
	cout << "Connected to server." << endl;
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

//=======================================	new functions go here
/*
 * Requests a list of game names from the server and returns it.
 * It is assumed that the list is returned in order, with the first item returned being the length of the list.
 * @return - a list of pointers to strings, the first element is the length of the rest of the list.
 */
char** Client::listGames() {
	int n, list_length, str_len;
	char** out;
	char command[11] = "list_games";
	//send the command "list_games" to the server.
	writeCommand(command, 11);
	//read list length
	n = read(clientSocket, &list_length, sizeof(list_length));
	if (n == -1) {
		throw "listGames()| Error reading list_length from socket";
	}
	//allocate space for string list
	out = (char**)malloc((list_length + 1) * sizeof(char*));
	//put the list length as its first element, it is assumed to be less than 255
	out[0] = (char*)malloc(sizeof(char));
	out[0][0] = (char)list_length;
	//read remaining strings
	for (int i = 0; i < list_length; i++) {
		n = read(clientSocket, &str_len, sizeof(str_len));
		if (n == -1) {
			throw "listGames()| Error reading str_len from socket";
		}
		out[i] = (char*)malloc(sizeof(char) * str_len);
		n = read(clientSocket, out[i], sizeof(char) * str_len);
		if (n == -1) {
			throw "listGames()| Error reading string from socket";
		}
	}
	return out;
}
/*
 * Tells the server that it wishes to join a game whose name is <name>.
 * @param - "join <name>"
 * @return - 1 if it joined succsesfully, 0 otherwise
 */
int Client::joinGame(char* command) {
	int n, succsus;
	writeCommand(command, commandLength(command));
	//reads the servers responese.
	n = read(clientSocket, &succsus, sizeof(succsus));
	if (n == -1) {
		throw "joinGame()| Error reading succsus from socket";
	}
	return succsus;
}
/*
 * Tells the server that it wants to start a new game with a name given in the command.
 * @param - "start <name>"
 * @return - 1 if it started succsesfully, 0 otherwise
 */
int Client::startGame(char* command) {
	int n, succsus;
	writeCommand(command, commandLength(command));
	//reads the servers responese.
	n = read(clientSocket, &succsus, sizeof(succsus));
	if (n == -1) {
		throw "joinGame()| Error reading succsus from socket";
	}
	return succsus;
}
/*
 * Tells the server that it wants to close a game with the name given in the command.
 * @param - "close <name>"
 * @return - 1 if it closed succsesfully, 0 otherwise
 */
int Client::closeGame(char* command) {
	int n, succsus;
	writeCommand(command, commandLength(command));
	//reads the servers responese.
	n = read(clientSocket, &succsus, sizeof(succsus));
	if (n == -1) {
		throw "joinGame()| Error reading succsus from socket";
	}
	return succsus;
}
/*
 * Writes the length of a command and then the command itself to the server.
 * @param command - a pointer to the command to be written.
 * @param length - the length of said command.
 */
void Client::writeCommand(char* command, int length) {
	int n;
	n = write(clientSocket, &length, sizeof(length));
	if (n == -1) {
		throw "Error writing str_len of list_games to socket";
	}
	n = write(clientSocket, command, length * sizeof(char));
	if (n == -1) {
		throw "Error writing list_games command to socket";
	}
}
/*
 * Gets a string and returns its length.
 */
int Client::commandLength(char* command) {
	int i = 0, len = 0;
	while (command[i] != '\0') {
		i++;
		len++;
	}
	return len;
}
