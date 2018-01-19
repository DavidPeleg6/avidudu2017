#include "headersS/PrintListCommand.h"
/*
 * Constructor for the command, sets the appropriate variablees.
 */
PrintListCommand::PrintListCommand(GameManager *info): clientSocket(0), info(info) {
	handler = new SocketHandler();
}
/*
 * Destructor - does nothing.
 */
PrintListCommand::~PrintListCommand() {
	delete handler;
}

/*
 * method to set up socket to send the game list to
 */
void PrintListCommand::setArgs(vector<string> args, int clientSocket) {
	this -> clientSocket = clientSocket;
}
/*
 * Executes the command, sending a list of avilable games to the user.
 */
bool PrintListCommand::execute() {
	vector<Games>* deadGames = info -> getWaitingGames();
	//send client the size of the games list
	handler->passInt(clientSocket, deadGames->size());
	if(deadGames->empty()) {
		return true;
	}
	vector<Games>::iterator it;
	for(it = deadGames->begin(); it != deadGames->end(); it++) {
		int nameSize = it -> name.size();
		const char* name = (it -> name).c_str();
		handler->passString(clientSocket, nameSize, name);
	}
	delete deadGames;
	clientSocket = 0;
	//keep getting input
	return true;
}
