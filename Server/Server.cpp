#include "headersS/Server.h"
#include <stdlib.h>
#include <pthread.h>
#include <cstdlib>
#define MAX_CONNECTED_CLIENTS 10
#define ERROR 0

int clientAmount = 0;

struct ServerInfo {
	CommandManager* manager;
	Server* server;
	int clientSocket;
};
/*
 * a constructor for Server
 * @param port = a port (int) number to set up server
 * @param manager = a CommandManager class to manage server actions
 */
Server::Server(int port, CommandManager* manager): port(port), serverSocket(0), manager(manager) {
	cout << "Server innitialized" << endl;
}
/*
 * This function waits for "exit" to know to just kill the stupid server already no one even reads these.
 */
void* waitToDie(void* mang) {
	ServerInfo *info = (ServerInfo*)mang;
	string s;
	cin >> s;
	char* msg = new char[s.length() + 1];
	strcpy(msg, s.c_str());
	Command *killCommand = info->manager->getCommand(msg, 0);
	killCommand->execute(info->server);
	delete[] msg;
	delete info;
	return NULL;
	//throw "Manual server shutdown.";
}

/*
 * a method for handling all commands received from client - might become threaded later
 * @param clientSocket = the socket of the calling client
 */
void *handleClient(void* info) {
	ServerInfo *comInfo = (ServerInfo*) info;
	char* msg;
	while(true) {
		//get an input string from client
		msg = comInfo->server->getString(comInfo->clientSocket);
		if(msg == NULL) {
			cout << "Error reading from client" << endl;
			const char* cls = "close";
			Command *command = comInfo->manager->getCommand(cls, comInfo->clientSocket);
			command->execute(comInfo->server);
			return NULL; //todo fix this
		}
		//get appropriate command from the manager and execute
		Command *command = comInfo->manager->getCommand(msg, comInfo->clientSocket);
		command -> execute(comInfo->server);
	}
}

/*
 * a method for running the mainframe of the server
 */
void Server::start() {

	pthread_t threads[MAX_CONNECTED_CLIENTS + 1];


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


	//threaded server suicide
	try {
		ServerInfo *info = new ServerInfo();
		info->manager = manager;
		info->server = this;
		int rc = pthread_create(&threads[0], NULL, waitToDie, (void*)info);
		if (rc) {
			cout << "Thread fail w/e." << endl;
			delete(info);
			exit(-1);
		}
	} catch(const char* msg) {
		cout << msg << endl;
		return;
	}





	// Start listening to incoming connections
	listen(serverSocket, MAX_CONNECTED_CLIENTS);
	// Define the client socket's structures
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen;
	bool printflag = true;
	while(true) {
		if(clientAmount == MAX_CONNECTED_CLIENTS) {
			if(printflag) {
				cout << "max client amount reached, holding connections" << endl;
				printflag = false;
			}
			continue;
		}
		cout << "Waiting for client connections..." << endl;
		// Accept a new client connection
		int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress,
				&clientAddressLen);
		if(clientSocket == -1) {
			throw "Error on accept client";
		}
		ServerInfo *comInfo = new ServerInfo();
		comInfo->manager = manager;
		comInfo->server = this;
		comInfo->clientSocket = clientSocket;
		cout << "Client connected: " << clientSocket << endl;
		try {
			int rc = pthread_create(&threads[clientAmount], NULL, handleClient, (void*)comInfo);
			clientAmount++;
			if (rc) {
				cout << "Thread fail w/e." << endl;
				delete(comInfo);
				exit(-1);
			}
		} catch(const char *msg) {
			cout << "handleclients crashed coz: " << msg << endl;
			delete(comInfo);
			close(clientSocket);
			clientAmount--;
			printflag = true;
		}
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
	int size = stringSize+1;
	int n = write(clientSocket, &size, sizeof(size));
	if(n <= 0) {
		return ERROR;
	}
	n = write(clientSocket, message, size);
	return 1;
}

/*
 * closes a given socket
 * clientSocket = (int) socket to be closed
 */
void Server::closeSocket(int clientSocket) {
	cout << "socket closed " << clientSocket << endl;
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
		throw ERROR;
	}
	return 1;
}

