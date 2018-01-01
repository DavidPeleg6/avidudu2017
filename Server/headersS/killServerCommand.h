/*
 * killServerCommand.h
 */

#ifndef KILLSERVERCOMMAND_H_
#define KILLSERVERCOMMAND_H_

#include "Command.h"
#include "GameManager.h"

class killServerCommand: public Command {
public:
	killServerCommand(GameManager *info);
	virtual ~killServerCommand();
	void setArgs(vector<string> args, int socket);
	void execute();

private:
	GameManager *info;
};

#endif /* KILLSERVERCOMMAND_H_ */
