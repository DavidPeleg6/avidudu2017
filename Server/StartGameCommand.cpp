/*
 * StartGameCommand.cpp
 */

#include "headersS/StartGameCommand.h"
#include "headersS/Server.h"

StartGameCommand::StartGameCommand(GameManager *info): info(info), player1Socket(0){
}

StartGameCommand::~StartGameCommand() {
}

void StartGameCommand::setArgs(vector<string> args, int socket) {
	name.assign(args.front());
	player1Socket = socket;
}

void StartGameCommand::execute(Server *server) {
	bool success = info->addGame(name,player1Socket);
	if(success) {
		server->passInt(player1Socket, 1);
	} else {
		server->passInt(player1Socket, -1);
		server->closeSocket(player1Socket);
	}
}
