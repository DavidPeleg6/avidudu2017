#include "headersS/CloseGameCommand.h"
/*
 * Constructor - Makes a new command for closing a game.
 */
CloseGameCommand::CloseGameCommand(GameManager *info): info(info) ,target(0){
	handler = new SocketHandler();
}
/*
 * Destructor - delete the handeler.
 */
CloseGameCommand::~CloseGameCommand() {
	delete handler;
}
/*
 * Sets the target socket for the game to be closed.
 */
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
	//stop getting input
	return false;
}
