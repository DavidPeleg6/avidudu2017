#include "headersS/Server.h"
#include <stdlib.h>
#include <pthread.h>
#include <cstdlib>
#define MAX_CONNECTED_CLIENTS 10

int clientAmount = 0;
bool alive = true;
bool printflag = true;



struct ServerInfo {
	CommandManager* manager;
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
static void* waitToDie(void* mang) {
	ServerInfo *info = (ServerInfo*)mang;
	string s;
	cin >> s;
	char* msg = new char[s.length() + 1];
	strcpy(msg, s.c_str());
	Command *killCommand = info->manager->getCommand(msg, 0);
	killCommand->execute();
	delete[] msg;
	delete info;
	alive = false;
	throw "Manual server shutdown.";
}

/*
 * a method for handling all commands received from client - might become threaded later
 * @param clientSocket = the socket of the calling client
 */
static void *handleClient(void* info) {
	ServerInfo *comInfo = (ServerInfo*) info;
	char* msg;
	while(true) {
		//get an input string from client
		msg = getString(comInfo->clientSocket);
		if(msg == NULL) {
			cout << "Error reading from client" << endl;
			const char* cls = "close";
			Command *command = comInfo->manager->getCommand(cls, comInfo->clientSocket);
			command->execute();
			cout << "close command" << endl;
			close(comInfo->clientSocket);
			delete(comInfo);
			printflag = true;
			clientAmount--;
			return (void*) "server closed "; //todo fix this
		}
		//get appropriate command from the manager and execute
		Command *command = comInfo->manager->getCommand(msg, comInfo->clientSocket);
		command -> execute();
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
		throw "Error on binding2";
	}
	cout << "Server started" << endl;


	//threaded server suicide
	try {
		ServerInfo *info = new ServerInfo();
		info->manager = manager;
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
	while(true) {
		if(!alive) {
			cout << "server terminated " << endl;
			break;
		}
		cout << "Waiting for client connections..." << endl;
		// Accept a new client connection
		int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress,
				&clientAddressLen);
		if(clientSocket == -1) {
			return;
		}
		if(clientAmount == MAX_CONNECTED_CLIENTS) {
			if(printflag) {
				cout << "max client amount reached, holding connections" << endl;
				printflag = false;
			}
			passInt(clientSocket, ERROR);
			close(clientSocket);
			continue;
		}
		passInt(clientSocket, SUCCESS);
		ServerInfo *comInfo = new ServerInfo();
		comInfo->manager = manager;
		comInfo->clientSocket = clientSocket;
		cout << "Client connected: " << clientSocket << endl;
			int rc = pthread_create(&threads[clientAmount], NULL, handleClient, (void*)comInfo);
			clientAmount++;
			if (rc) {
				cout << "Thread fail w/e." << endl;
				delete(comInfo);
				exit(-1);
			}
	}
}



/*
 * closes the server socket
 */
void Server::stop() {
	close(serverSocket);
}


