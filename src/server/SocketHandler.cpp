#include "headersS/SocketHandler.h"
#include <iostream>
using namespace std;
/*
 * Constructor and destructor, do nothing.
 */
SocketHandler::SocketHandler() { }
SocketHandler::~SocketHandler() { }
/*
 * a method to pass a given number to the client
 * @param clientSocket = a socket to write to (int)
 * @param num = a number to pass (int)
 * @return = int indicating success or fail
 */
int SocketHandler::passInt(int clientSocket, int num) {
	int n = write(clientSocket, &num, sizeof(int));
	if(n <= 0) {
		return ERROR;
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
int SocketHandler::passString(int clientSocket, int stringSize, const char* message) {
	cout << message << " client num: " << clientSocket << endl; //TODO delete
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
char* SocketHandler::getString(int clientSocket) {
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
	return message;
}

