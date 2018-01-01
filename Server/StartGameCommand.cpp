/*
 * StartGameCommand.cpp
 */

#include "headersS/StartGameCommand.h"

StartGameCommand::StartGameCommand(GameManager *info): info(info), player1Socket(0){
	handler = new SocketHandler();
}

StartGameCommand::~StartGameCommand() {
	delete handler;
}

void StartGameCommand::setArgs(vector<string> args, int socket) {
	name.assign(args.front());
	player1Socket = socket;
}

bool StartGameCommand::execute() {
	bool success = info->addGame(name,player1Socket);
	//cout << success << endl;
	if(success) {
		handler->passInt(player1Socket, 1);
		//should close thread
		return false;
	} else {
		handler->passInt(player1Socket, -1);
		//shouldnt close thread
		return false;
	}
}
