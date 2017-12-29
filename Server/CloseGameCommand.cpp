/*
 * CloseGameCommand.cpp
 */

#include "headersS/CloseGameCommand.h"
#include "headersS/Server.h"

CloseGameCommand::CloseGameCommand(GameManager *info): info(info) {
}

CloseGameCommand::~CloseGameCommand() {
}

void CloseGameCommand::setArgs(vector<string> args, int socket) {
	target = args.front();
}

void CloseGameCommand::execute(Server* server) {
	int *game = info->getGame(target);
	if(game != NULL) {
		server->closeSocket(game[0]);
		server->closeSocket(game[1]);
		delete game;
	}
	info->closeGame(target);
}
