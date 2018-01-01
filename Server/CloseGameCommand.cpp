/*
 * CloseGameCommand.cpp
 */

#include "headersS/CloseGameCommand.h"
#include "headersS/Server.h"

CloseGameCommand::CloseGameCommand(GameManager *info): info(info) ,target(0){
}

CloseGameCommand::~CloseGameCommand() {
}

void CloseGameCommand::setArgs(vector<string> args, int socket) {
	target = socket;
}

void CloseGameCommand::execute() {
	const char* killMsg = "SHUTDOWN";
	int *game = info->getGame(target);
	if(game != NULL) {
		passString(game[0], 8, killMsg);
		close(game[0]);
		if(game[2]) {
			passString(game[1], 8, killMsg);
			close(game[1]);
		}
		delete []game;
	}
	info->closeGame(target);
}
