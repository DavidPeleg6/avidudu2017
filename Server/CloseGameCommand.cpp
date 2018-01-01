/*
 * CloseGameCommand.cpp
 */

#include "headersS/CloseGameCommand.h"

CloseGameCommand::CloseGameCommand(GameManager *info): info(info) ,target(0){
	handler = new SocketHandler();
}

CloseGameCommand::~CloseGameCommand() {
	delete handler;
}

void CloseGameCommand::setArgs(vector<string> args, int socket) {
	target = socket;
}
/*
 * close game command
 * return true, always closes thread
 * will get a player in a game and close his an his opponent's sockets
 */
bool CloseGameCommand::execute() {
	const char* killMsg = "SHUTDOWN";
	int *players = info->getGame(target);
	handler->passString(players[0], 8, killMsg);
	close(players[0]);
	handler->passString(players[1], 8, killMsg);
	close(players[1]);
	delete []players;
	info->closeGame(target);
	//close thread
	return true;
}
