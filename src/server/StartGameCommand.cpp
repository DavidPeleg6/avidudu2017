#include "headersS/StartGameCommand.h"
/*
 * Constructor - Makes a command which starts a game.
 */
StartGameCommand::StartGameCommand(GameManager *info): info(info), player1Socket(0){
	handler = new SocketHandler();
}
/*
 * Destructor - Delete the command.
 */
StartGameCommand::~StartGameCommand() {
	delete handler;
}
/*
 * Sets the commands' arguements.
 */
void StartGameCommand::setArgs(vector<string> args, int socket) {
	name.assign(args.front());
	player1Socket = socket;
}
/*
 * Executes the command, starting a new game.
 */
bool StartGameCommand::execute() {
	bool success = info->addGame(name,player1Socket);
	//cout << success << endl;
	if(success) {
		handler->passInt(player1Socket, 1);
		//keep getting input
		return true;
	} else {
		handler->passInt(player1Socket, -1);
		//keep getting input
		return true;
	}
}
