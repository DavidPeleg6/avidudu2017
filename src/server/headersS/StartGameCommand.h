/*
 * StartGameCommand.h
 */

#ifndef STARTGAMECOMMAND_H_
#define STARTGAMECOMMAND_H_

#include "Command.h"
#include "GameManager.h"

class StartGameCommand: public Command {
public:
	StartGameCommand(GameManager *info);
	~StartGameCommand();
	void setArgs(vector<string> args, int socket);
	bool execute();

private:
	GameManager *info;
	string name;
	int player1Socket;
	SocketHandler *handler;
};

#endif /* STARTGAMECOMMAND_H_ */
