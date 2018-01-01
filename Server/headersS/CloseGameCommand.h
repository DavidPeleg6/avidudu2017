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
	void execute();

private:
	GameManager *info;
	int target;
};



#endif /* HEADERSS_CLOSEGAMECOMMAND_H_ */
