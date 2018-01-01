/*
 * StartGameCommand.cpp
 */

#include "headersS/StartGameCommand.h"
#include "headersS/Server.h"

StartGameCommand::StartGameCommand(GameManager *info): info(info), player1Socket(0){ }

StartGameCommand::~StartGameCommand() {
}

void StartGameCommand::setArgs(vector<string> args, int socket) {
	name.assign(args.front());
	player1Socket = socket;
}

void StartGameCommand::execute() {
	bool success = info->addGame(name,player1Socket);
	//cout << success << endl;
	if(success) {
		passInt(player1Socket, 1);
	} else {
		passInt(player1Socket, -1);
	}
}
