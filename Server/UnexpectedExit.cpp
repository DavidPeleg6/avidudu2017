#include "headersS/UnexpectedExit.h"
/*
 * Creates a new command which handels unexpects exits.
 */
UnexpectedExit::UnexpectedExit(GameManager *info): info(info) ,target(0) {
	handler = new SocketHandler();
}
/*
 * Deletes this command.
 */
UnexpectedExit::~UnexpectedExit() {
	delete handler;
}
/*
 * Sets the arguments for this command.
 */
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

