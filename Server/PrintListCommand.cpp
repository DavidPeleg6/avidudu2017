/*
 * PrintListCommand.cpp
 */

#include "headersS/PrintListCommand.h"

PrintListCommand::PrintListCommand(GameManager *info): clientSocket(0), info(info) {
	handler = new SocketHandler();
}

//does nothing
PrintListCommand::~PrintListCommand() {
	delete handler;
}

/*
 * method to set up socket to send the game list to
 */
void PrintListCommand::setArgs(vector<string> args, int clientSocket) {
	this -> clientSocket = clientSocket;
}

bool PrintListCommand::execute() {
	vector<Games>* deadGames = info -> getWaitingGames();
	//send client the size of the games list
	handler->passInt(clientSocket, deadGames->size());
	if(deadGames->empty()) {
		return false;
	}
	vector<Games>::iterator it;
	for(it = deadGames->begin(); it != deadGames->end(); it++) {
		int nameSize = it -> name.size();
		const char* name = (it -> name).c_str();
		handler->passString(clientSocket, nameSize, name);
	}
	delete deadGames;
	clientSocket = 0;
	//dont close thread
	return false;
}
