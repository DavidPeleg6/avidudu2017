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
	virtual ~StartGameCommand();
	void setArgs(vector<string> args, int socket);
	void execute(Server *server);

private:
	GameManager *info;
	string name;
	int player1Socket;
};

#endif /* STARTGAMECOMMAND_H_ */
