/*
 * PrintListCommand.cpp
 */

#include "headersS/PrintListCommand.h"
#include "headersS/Server.h"

PrintListCommand::PrintListCommand(GameManager *info): clientSocket(0), info(info) {
}

//does nothing
PrintListCommand::~PrintListCommand() {
}

/*
 * method to set up socket to send the game list to
 */
void PrintListCommand::setArgs(vector<string> args, int clientSocket) {
	this -> clientSocket = clientSocket;
}

void PrintListCommand::execute(Server *server) {
	vector<Games> deadGames = info -> getWaitingGames();
	//send client the size of the games list
	server -> passInt(clientSocket, deadGames.size());
	vector<Games>::iterator it;
	for(it = deadGames.begin(); it != deadGames.end(); ++it) {
		int nameSize = it -> name.size();
		const char* name = (it -> name).c_str();
		server ->passString(clientSocket, nameSize, name);
	}
	clientSocket = 0;
}
