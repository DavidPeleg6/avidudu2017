/*
 * JoinGameCommand.h
 */

#ifndef JOINGAMECOMMAND_H_
#define JOINGAMECOMMAND_H_

#include "Command.h"
#include "GameManager.h"

class JoinGameCommand: public Command {
public:
	JoinGameCommand(GameManager *info);
	~JoinGameCommand();
	void setArgs(vector<string> args, int socket);
	bool execute();

private:
	GameManager *info;
	string name;
	int player2Socket;
	SocketHandler *handler;
};

#endif /* JOINGAMECOMMAND_H_ */
