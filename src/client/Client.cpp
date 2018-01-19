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
#include <sstream>
#define REJECTED 0
#define CONNECTED 1
using namespace std;
/*
 * Constructor, makes a new client object.
 * @param serverIP - the IP adress of the server the client will connect to.
 * @param serverPort - the port it will use to connect to the server.
 */
Client::Client(const char *serverIP, int serverPort):
	serverIP(serverIP), serverPort(serverPort),
	clientSocket(0) { }
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
	int serverSocket = connect(clientSocket, (struct sockaddr
			*)&serverAddress, sizeof(serverAddress));
	if (serverSocket == -1) {
		throw "Error connecting to server";
	}
	int conrected = readInt();
	if (conrected == REJECTED) {
		throw "Server full.";
	}
	cout << "Connected to server." << endl;
}
/*
 * Sends a move to the other player.
 * @param x - the x coordinate
 * @param y - the y coordinate
 */
void Client::SendMove(int x, int y) {
	stringstream send;
	send << "play " << x << " " << y;
	const char* sendc = send.str().c_str();
	writeCommand(sendc, commandLength(sendc));
}
/*
 * Gets a move from the other player which will be acted out on this instance of the game.
 */
int* Client::GetMove() {
	int n, len, x, y;
	char* str;
	stringstream ss;
	string play_absorver;
	n = read(clientSocket, &len, sizeof(len));
	if (n == -1) {
		throw "Error reading len from socket";
	}
	str = (char*)malloc(sizeof(char) * len);
	n = read(clientSocket, str, sizeof(char) * len);
	if (n == -1) {
		throw "Error reading string from socket";
	}
	if (strcmp(str, "SHUTDOWN") == 0) {
		int* move = (int*)calloc(2, sizeof(int));
		move[0] = -2;
		move[1] = -2;
		return move;
	}
	ss << str;
	ss >> play_absorver >> x >> y;
	free(str);
	int* move = (int*)calloc(2, sizeof(int));
	move[0] = x;
	move[1] = y;
	return move;
}
//=======================================	new functions go here
/*
 * Requests a list of game names from the server and returns it.
 * It is assumed that the list is returned in order, with the first item returned being the length of the list.
 * @return - a list of pointers to strings, the first element is the length of the rest of the list.
 */
char** Client::listGames(const char* command) {
	int n, list_length, str_len;
	char** out;
	//send the command "list_games" to the server.
	writeCommand(command, commandLength(command));
	//read list length
	n = read(clientSocket, &list_length, sizeof(list_length));
	if (n == -1) {
		throw "listGames()| Error reading list_length from socket";
	}
	//allocate space for string list
	out = (char**)malloc((list_length + 1) * sizeof(char*));
	//put the list length as its first element, it is assumed to be less than 255
	out[0] = (char*)malloc(sizeof(int));
	*out[0] = list_length;
	//read remaining strings
	for (int i = 1; i < list_length + 1; i++) {
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
 * Writes the length of a command and then the command itself to the server.
 * @param command - a pointer to the command to be written.
 * @param length - the length of said command.
 */
void Client::writeCommand(const char* command, int length) {
	int n;
	n = write(clientSocket, &length, sizeof(length));
	if (n == 0) {
		throw "Server unexpectedly shut down.";
	}
	if (n == -1) {
		throw "Error writing str_len of list_games to socket";
	}
	//confirmation from server
	if (readInt() != 1) {
		throw "Game has ended due to unexpected server shutdown.";
	}
	//that str len was recieved.
	n = write(clientSocket, command, length * sizeof(char));
	if (n == 0) {
		throw "Server unexpectedly shut down.";
	}
	if (n == -1) {
		throw "Error writing list_games command to socket";
	}
}
/*
 * Gets a string and returns its length.
 */
int Client::commandLength(const char* command) {
	int i = 0, len = 1;
	while (command[i] != '\0') {
		i++;
		len++;
	}
	return len;
}
/*
 * Passes a simple command to the server.
 * Simple commands are ones whose output is a simple number.
 * @param command - the command to be passed.
 * @return the values the server returned.
 */
int Client::passSimpleCommand(const char* command) {
	int n, succsus;
	writeCommand(command, commandLength(command));
	//reads the servers responese.
	n = read(clientSocket, &succsus, sizeof(succsus));
	if (n == -1) {
		throw "Error reading succses from socket";
	}
	return succsus;
}
/*
 * Reads one integer from the server and returns it.
 */
int Client::readInt() {
	int n, val;
	//reads the servers responese.
	n = read(clientSocket, &val, sizeof(val));
	if (n == -1 || n == 0) {
		throw "Game has ended due to unexpected server shutdown.";
	}
	return val;
}
