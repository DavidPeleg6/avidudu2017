/*
 * StartGameCommand.h
 */

#ifndef STARTGAMECOMMAND_H_
#define STARTGAMECOMMAND_H_

#include "Command.h"
#include "GameManager.h"

class StartGameCommand: public Command {
public:
	StartGameCommand();
	virtual ~StartGameCommand();

private:
	GameManager *info;
};

#endif /* STARTGAMECOMMAND_H_ */
