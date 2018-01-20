#include "headersS/Server.h"

#define THREAD_NUM 5
#define LISTEN_QUEUE 50

vector<int> clients;
pthread_mutex_t Server::serverLock;

void getInput(void* args);
void executeCommand(void* args);

struct ServerInfo {
	CommandManager* manager;
	int clientSocket;
	pthread_mutex_t serverLock;
	int serverSocket;
	ThreadPool* pool;
};

struct ClientInfo {
	CommandManager* manager;
	Command* command;
	int clientSocket;
	pthread_mutex_t serverLock;
	ThreadPool* pool;
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
 * a method for listening to all connections
 */
void* listenClients(void* args) {
	ServerInfo *info = (ServerInfo*)args;
	SocketHandler *handler = new SocketHandler();
	// Start listening to incoming connections
	listen(info->serverSocket, LISTEN_QUEUE);
	// Define the client socket's structures
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen;
	while(true) {
		cout << "Waiting for client connections..." << endl;
		// Accept a new client connection
		int clientSocket = accept(info->serverSocket, (struct sockaddr*)&clientAddress,
				&clientAddressLen);
		if(clientSocket == -1) {
			continue;
		}
		//add a new client to the vector
		clients.push_back(clientSocket);
		//confirm connection with client
		handler->passInt(clientSocket, SUCCESS);
		ClientInfo *taskInfo = new ClientInfo();
		//start struct for thread
		taskInfo->manager = info->manager;
		taskInfo->clientSocket = clientSocket;
		taskInfo->pool = info->pool;
		taskInfo->serverLock = info->serverLock;
		Task *task = new Task(getInput, (void*) taskInfo);
		taskInfo->pool->addTask(task);
		cout << "Client connected: " << clientSocket << endl;
	}
	delete handler;
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
	//server socket initialize
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

	//initialize a thread pool
	ThreadPool *pool = new ThreadPool(THREAD_NUM);
	//initialize listening socket
	ServerInfo *info = new ServerInfo();
	info->manager = manager;
	info->serverLock = serverLock;
	info->serverSocket = serverSocket;
	info->pool = pool;
	int rc = pthread_create(&listenThread, NULL, listenClients, (void*)info);
	if (rc) {
		cout << "Thread make fail." << endl;
		delete info;
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
			pthread_cancel(listenThread);
			pthread_mutex_unlock(&(info->serverLock));
			break;
		}
	}
	//close the thread pool
	pool->terminate();
	delete pool;
}
/*
 * closes the server socket
 */
void Server::stop() {
	close(serverSocket);
}

/*
 * getInput task a task method to be added to the queue
 * will get input and issue a commmand task accordingly
 * @param args the struct with everything needed for getting input from user
 */
void getInput(void* args) {
	ClientInfo *info = (ClientInfo *) args;
	SocketHandler *handle = new SocketHandler();
	char* msg;
	//get an input string from client
	msg = handle->getString(info->clientSocket);
	if(msg == NULL) {
		//handling the extreme case of client shutting out unexpectedly
		pthread_mutex_lock(&(info->serverLock));
		vector<int>::iterator it;
		for(it = clients.begin(); *it != info->clientSocket && it != clients.end(); it++) {
			cout << " client num " << *it << endl;
		}
		clients.erase(it);
		close(info->clientSocket);
		//start an unexpected exit message
		Command *unexpected_exit = info->manager->getCommand("unexpected", info->clientSocket);
		unexpected_exit -> execute();
		pthread_mutex_unlock(&(info->serverLock));
		return;
	}

	//get appropriate command from the manager and add it execute as a new task
	Command *command = info->manager->getCommand(msg, info->clientSocket);
	//get params ready for command execution
	ClientInfo *exeInfo = new ClientInfo();
	//start struct for thread
	exeInfo->manager = info->manager;
	exeInfo->clientSocket = info->clientSocket;
	exeInfo->pool = info->pool;
	exeInfo->serverLock = info->serverLock;
	exeInfo->command = command;
	//add a new task to the queue
	Task *task = new Task(executeCommand, (void*)exeInfo);
	info->pool->addTask(task);
	delete handle;
	delete info;
}

/*
 * executeCommand task a task method to be added to the queue
 * will execute a command given in the struct and will add a new get input task according
 * to the return value of command
 * @param args the struct with everything needed for getting executing command
 */
void executeCommand(void* args) {
	bool clientDone = false;
	ClientInfo *info = (ClientInfo *) args;
	clientDone = info->command->execute();
	if(!clientDone) {
		//find the client and remove it from the vector
		pthread_mutex_lock(&(info->serverLock));
		vector<int>::iterator it;
		for(it = clients.begin(); it != clients.end(); it++) {
			if(*it == info->clientSocket) {
				clients.erase(it);
				break;
			}
		}
		pthread_mutex_unlock(&(info->serverLock));
		return;
	}
	//get ready for getting another input from client
	ClientInfo *inputInfo = new ClientInfo();
	inputInfo->clientSocket = info->clientSocket;
	inputInfo->manager = info->manager;
	inputInfo->pool = info->pool;
	inputInfo->serverLock = info->serverLock;
	//add a new task to the queue
	Task *task = new Task(getInput, (void*) inputInfo);
	info->pool->addTask(task);
	delete info;
}




