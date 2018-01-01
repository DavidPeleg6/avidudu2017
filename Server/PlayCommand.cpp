/*
 * PlayCommand.cpp
 */

#include "headersS/PlayCommand.h"
#include "headersS/Server.h"

PlayCommand::PlayCommand(GameManager* info): info(info), senderSocket(0) {
}

PlayCommand::~PlayCommand() {
}

void PlayCommand::setArgs(vector<string> args, int socket) {
	senderSocket = socket;
	stringstream ss;
	ss << args.at(0) << " " << args.at(1);
	ss >> move[0] >> move[1];
}

void PlayCommand::execute() {
	int opponent = info->getOpponent(senderSocket);
	stringstream send;
	send << "play " << move[0] << " " << move[1];
	int messageSize = send.str().size();
	const char* sendc = send.str().c_str();
	passString(opponent, messageSize, sendc);
}
