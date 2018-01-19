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
	bool execute();

private:
	GameManager *info;
	int move[2];
	int senderSocket;
	SocketHandler *handler;
};

#endif /* PLAYCOMMAND_H_ */
