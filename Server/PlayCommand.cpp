/*
 * PlayCommand.cpp
 */

#include "headersS/PlayCommand.h"
#include "headersS/Server.h"

PlayCommand::PlayCommand(GameManager* info): info(info), senderSocket(0) {
	handler = new SocketHandler();
}

PlayCommand::~PlayCommand() {
	delete handler;
}

void PlayCommand::setArgs(vector<string> args, int socket) {
	senderSocket = socket;
	stringstream ss;
	ss << args.at(0) << " " << args.at(1);
	ss >> move[0] >> move[1];
}

bool PlayCommand::execute() {
	int opponent = info->getOpponent(senderSocket);
	stringstream send;
	send << "play " << move[0] << " " << move[1];
	int messageSize = send.str().size();
	const char* sendc = send.str().c_str();
	if(handler->passString(opponent, messageSize, sendc) == 0) {
		info->closeGame(senderSocket);
		close(senderSocket);
	}
	//dont close thread
	return false;
}
