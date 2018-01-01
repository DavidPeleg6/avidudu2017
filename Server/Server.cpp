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
};
/*
 * a constructor for Server
 * @param port = a port (int) number to set up server
 * @param manager = a CommandManager class to manage server actions
 */
Server::Server(int port, CommandManager* manager): port(port), serverSocket(0), manager(manager) {
	handler = new SocketHandler();
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
	pthread_mutex_lock(&(info->serverLock));
	killCommand->execute();
	vector<int>::iterator it;
	for(it = clients.begin(); it != clients.end(); it++) {
		close(*it);
	}
	delete[] msg;
	delete info;
	alive = false;
	pthread_mutex_unlock(&(info->serverLock));
	delete info;
	return NULL;
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
	ServerInfo *info = new ServerInfo();
	info->manager = manager;
	info->serverLock = serverLock;
	int rc = pthread_create(&threads[0], NULL, waitToDie, (void*)info);
	if (rc) {
		cout << "Thread fail w/e." << endl;
		delete(info);
		exit(-1);
	}

	// Start listening to incoming connections
	listen(serverSocket, MAX_CONNECTED_CLIENTS);
	// Define the client socket's structures
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen;
	while(alive) {
		cout << "Waiting for client connections..." << endl;
		// Accept a new client connection
		int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress,
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
		pthread_mutex_lock(&serverLock);
		clients.push_back(clientSocket);
		pthread_mutex_unlock(&serverLock);
		//confirm connection with client
		handler->passInt(clientSocket, SUCCESS);
		ServerInfo *comInfo = new ServerInfo();
		//start struct for thread
		comInfo->manager = manager;
		comInfo->clientSocket = clientSocket;
		comInfo->handler = handler;
		comInfo->serverLock = serverLock;
		cout << "Client connected: " << clientSocket << endl;
		int rc = pthread_create(&threads[clients.size()], NULL, handleClient, (void*)comInfo);
		if (rc) {
			cout << "Thread fail w/e." << endl;
			delete(comInfo);
			exit(-1);
		}
	}
	cout << "server terminated " << endl;
}



/*
 * closes the server socket
 */
void Server::stop() {
	close(serverSocket);
	delete handler;
}


