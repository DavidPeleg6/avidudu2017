#include "headersS/Server.h"

#define MAX_CONNECTED_CLIENTS 10

vector<int> clients;
bool alive = true;
bool printflag = true;
pthread_mutex_t Server::serverLock;


struct ServerInfo {
	CommandManager* manager;
	SocketHandler *handler;
	int clientSocket;
	pthread_mutex_t serverLock;
	int serverSocket;
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
 * a method for handling all commands received from client - might become threaded later
 * @param clientSocket = the socket of the calling client
 */
static void *handleClient(void* info) {
	ServerInfo *comInfo = (ServerInfo*) info;
	bool shouldClose = false;
	char* msg;
	while(!shouldClose && alive) {
		//get an input string from client
		msg = comInfo->handler->getString(comInfo->clientSocket);
		if(msg == NULL) {
			cout << "Error reading from client" << endl;
			Command *unexpected_exit = comInfo->manager->getCommand("unexpected", comInfo->clientSocket);
			unexpected_exit -> execute();
			pthread_mutex_lock(&(comInfo->serverLock));
			//find dead link socket and delete it from array
			vector<int>::iterator it;
			for(it = clients.begin(); *it != comInfo->clientSocket; it++) { }
			clients.erase(it);
			close(comInfo->clientSocket);
			pthread_mutex_unlock(&(comInfo->serverLock));
			printflag = true;
			break;
		}
		//get appropriate command from the manager and execute
		Command *command = comInfo->manager->getCommand(msg, comInfo->clientSocket);
		shouldClose = command -> execute();
	}
	return (void*)SUCCESS;
}

/*
 * a method for listening to all connections
 */
static void* listenClients(void* args) {
	ServerInfo *info = (ServerInfo*)args;
	pthread_t threads[MAX_CONNECTED_CLIENTS + 1];
	SocketHandler *handler = new SocketHandler();
	// Start listening to incoming connections
	listen(info->serverSocket, MAX_CONNECTED_CLIENTS);
	// Define the client socket's structures
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen;
	while(alive) {
		cout << "Waiting for client connections..." << endl;
		// Accept a new client connection
		int clientSocket = accept(info->serverSocket, (struct sockaddr*)&clientAddress,
				&clientAddressLen);
		if(clientSocket == -1) {
			continue;
		}
		if(clients.size() == MAX_CONNECTED_CLIENTS) {
			if(printflag) {
				cout << "max client amount reached, holding connections" << endl;
				printflag = false;
			}
			handler->passInt(clientSocket, ERROR);
			close(clientSocket);
			continue;
		}
		//add a new client to the vector
		pthread_mutex_lock(&(info->serverLock));
		clients.push_back(clientSocket);
		pthread_mutex_unlock(&(info->serverLock));
		//confirm connection with client
		handler->passInt(clientSocket, SUCCESS);
		ServerInfo *comInfo = new ServerInfo();
		//start struct for thread
		comInfo->manager = info->manager;
		comInfo->clientSocket = clientSocket;
		comInfo->handler = handler;
		comInfo->serverLock = info->serverLock;
		cout << "Client connected: " << clientSocket << endl;
		int rc = pthread_create(&threads[clients.size()], NULL, handleClient, (void*)comInfo);
		if (rc) {
			cout << "Thread make fail." << endl;
			delete(comInfo);
			exit(-1);
		}
	}
	return (void*)NULL;
}
/*
 * a method for running the mainframe of the server
 */
void Server::start() {
	pthread_t listenThread;
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


	ServerInfo *info = new ServerInfo();
	info->manager = manager;
	info->serverLock = serverLock;
	info->serverSocket = serverSocket;
	int rc = pthread_create(&listenThread, NULL, listenClients, (void*)info);
	if (rc) {
		cout << "Thread make fail." << endl;
		delete(info);
		exit(-1);
	}


	//threaded server suicide
	string s;
	while(true) {
		cin >> s;
		if(!s.compare("exit")) {
			char* msg = new char[s.length() + 1];
			strcpy(msg, s.c_str());
			Command *killCommand = info->manager->getCommand(msg, 0);
			pthread_mutex_lock(&(info->serverLock));
			killCommand->execute();
			vector<int>::iterator it;
			for(it = clients.begin(); it != clients.end(); it++) {
				close(*it);
			}
			delete[] msg;
			alive = false;
			pthread_cancel(listenThread);
			pthread_mutex_unlock(&(info->serverLock));
			break;
		}
	}

	cout << "server terminated " << endl;
}
/*
 * closes the server socket
 */
void Server::stop() {
	close(serverSocket);
}


