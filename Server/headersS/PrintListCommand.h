/*
 * PrintListCommand.h
 */

#ifndef PRINTLISTCOMMAND_H_
#define PRINTLISTCOMMAND_H_

#include "Command.h"

class PrintListCommand: public Command {
public:
	PrintListCommand();
	void execute(vector<string> args);
	virtual ~PrintListCommand();
};

#endif /* PRINTLISTCOMMAND_H_ */
