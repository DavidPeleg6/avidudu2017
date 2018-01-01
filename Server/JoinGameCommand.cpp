/*
 * JoinGameCommand.cpp
 */

#include "headersS/JoinGameCommand.h"
#include "headersS/Server.h"

JoinGameCommand::JoinGameCommand(GameManager* info): info(info), player2Socket(0) {
}

JoinGameCommand::~JoinGameCommand() {
}

void JoinGameCommand::setArgs(vector<string> args, int socket) {
	name.assign(args.front());
	player2Socket = socket;
}

void JoinGameCommand::execute() {
	bool success = info->startGame(name, player2Socket);
	int opponent = info->getOpponent(player2Socket);
	if(success) {
		passInt(opponent, 1);
		passInt(player2Socket, 2);
	} else {
		passInt(player2Socket, -2);
	}
}
