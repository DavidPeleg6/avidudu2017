#include "headersS/PlayCommand.h"
#include "headersS/Server.h"
/*
 * Constructor - make a new play command.
 */
PlayCommand::PlayCommand(GameManager* info): info(info), senderSocket(0) {
	handler = new SocketHandler();
}
/*
 * Destructor - delete the handler.
 */
PlayCommand::~PlayCommand() {
	delete handler;
}
/*
 * Sets the play commands arguments to be the move to be sent and its target.
 */
void PlayCommand::setArgs(vector<string> args, int socket) {
	senderSocket = socket;
	stringstream ss;
	ss << args.at(0) << " " << args.at(1);
	ss >> move[0] >> move[1];
}
/*
 *	Sends the move data to the opponent of the user who sent the play command.
 */
bool PlayCommand::execute() {
	int opponent = info->getOpponent(senderSocket);
	if(opponent == 0) {
		return true;
	}
	stringstream send;
	send << "play " << move[0] << " " << move[1];
	cout << send << endl; //TODO delete
	int messageSize = send.str().size();
	const char* sendc = send.str().c_str();
	if(handler->passString(opponent, messageSize, sendc) == 0) {
		info->closeGame(senderSocket);
		close(senderSocket);
	}
	//game still alive
	return true;
}
