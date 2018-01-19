#include "headersS/JoinGameCommand.h"
/*
 * Makes a new command for joining a game.
 */
JoinGameCommand::JoinGameCommand(GameManager* info): info(info), player2Socket(0) {
	handler = new SocketHandler();
}
/*
 * Deletes the command for joining a game.
 */
JoinGameCommand::~JoinGameCommand() {
	delete handler;
}
/*
 * Sets the commands' arguements.
 */
void JoinGameCommand::setArgs(vector<string> args, int socket) {
	name.assign(args.front());
	player2Socket = socket;
}

/*
 * will get a game name and socket and will add the socket to the game if availible
 */
bool JoinGameCommand::execute() {
	bool success = info->startGame(name, player2Socket);
	int opponent = info->getOpponent(player2Socket);
	if(success) {
		//send players their colors
		handler->passInt(opponent, 1);
		handler->passInt(player2Socket, 2);
		//dont close thread
		return false;
	} else {
		handler->passInt(player2Socket, -2);
		//dont close thread
		return false;
	}
}
