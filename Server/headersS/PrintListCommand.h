/*
 * PrintListCommand.h
 */

#ifndef PRINTLISTCOMMAND_H_
#define PRINTLISTCOMMAND_H_

#include "Command.h"
#include "GameManager.h"

class PrintListCommand: public Command {
public:
	PrintListCommand(GameManager *info);
	void setArgs(vector<string> args, int clientSocket);
	void execute(Server *server);
	virtual ~PrintListCommand();

private:
	int clientSocket;
	GameManager *info;
};

#endif /* PRINTLISTCOMMAND_H_ */
