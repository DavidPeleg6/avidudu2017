/*
 * PlayCommand.h
 */

#ifndef PLAYCOMMAND_H_
#define PLAYCOMMAND_H_

#include "Command.h"
#include "GameManager.h"

class PlayCommand: public Command {
public:
	PlayCommand(GameManager *info);
	virtual ~PlayCommand();
	void setArgs(vector<string> args, int socket);
	void execute(Server *server);

private:
	GameManager *info;
	int move[2];
	int senderSocket;
};

#endif /* PLAYCOMMAND_H_ */
