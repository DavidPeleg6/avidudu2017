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
	bool execute();
	virtual ~PrintListCommand();

private:
	int clientSocket;
	GameManager *info;
	SocketHandler *handler;
};

#endif /* PRINTLISTCOMMAND_H_ */
