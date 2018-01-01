/*
 * killServerCommand.cpp
 */

#include "headersS/killServerCommand.h"
#include "headersS/Server.h"

killServerCommand::killServerCommand(GameManager *info): info(info) {

}

killServerCommand::~killServerCommand() {
}

//does nothing
void killServerCommand::setArgs(vector<string> args, int socket) {
}

void killServerCommand::execute() {
	cout << "Terminating server." << endl;
	const char* killMsg = "SHUTDOWN";
	vector<int> players = info->getAllPlayers();
	vector<int>::iterator it;
	for(it = players.begin(); it != players.end(); ++it) {
		//send socket int to server with the server crash close (= 0) message
		passString(*it, 8, killMsg);
		close(*it);
	}
	//throw "manual termination";
}
