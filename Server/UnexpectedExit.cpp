/*
 * UnexpectedExit.cpp
 */

#include "headersS/UnexpectedExit.h"

UnexpectedExit::UnexpectedExit(GameManager *info): info(info) ,target(0) {
	handler = new SocketHandler();
}

UnexpectedExit::~UnexpectedExit() {
	delete handler;
}

void UnexpectedExit::setArgs(vector<string> args, int socket) {
	target = socket;
}
/*
 * unexpected exit command
 * return true, always closes thread
 * will get a player in a game and close his opponents socket and game
 */
bool UnexpectedExit::execute() {
	int opponent = info->getOpponent(target);
	close(target);
	info->closeGame(target);
	//close thread
	return true;
}

