/*
 * CloseGameCommand.h
 */

#ifndef HEADERSS_CLOSEGAMECOMMAND_H_
#define HEADERSS_CLOSEGAMECOMMAND_H_

#include "Command.h"
#include "GameManager.h"

class CloseGameCommand: public Command {
public:
	CloseGameCommand(GameManager *info);
	~CloseGameCommand();
	void setArgs(vector<string> args, int socket);
	bool execute();

private:
	GameManager *info;
	int target;
	SocketHandler *handler;
};



#endif /* HEADERSS_CLOSEGAMECOMMAND_H_ */
