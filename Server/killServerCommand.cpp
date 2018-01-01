/*
 * killServerCommand.cpp
 */

#include "headersS/killServerCommand.h"

killServerCommand::killServerCommand(GameManager *info): info(info) {
	handler = new SocketHandler();
}

killServerCommand::~killServerCommand() {
	delete handler;
}

//does nothing
void killServerCommand::setArgs(vector<string> args, int socket) {
}
/*
 * a method for exiting the server, still not sure if it should exist as a command
 */
bool killServerCommand::execute() {
	const char* killMsg = "SHUTDOWN";
	vector<int> players = info->getAllPlayers();
	vector<int>::iterator it;
	for(it = players.begin(); it != players.end(); ++it) {
		//send socket int to server with the server crash close (= 0) message
		handler->passString(*it, 8, killMsg);
	}
	return true;
	//throw "manual termination";
}
