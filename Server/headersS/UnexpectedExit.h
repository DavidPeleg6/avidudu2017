/*
 * UnexpectedExit.h
 */

#ifndef UNEXPECTEDEXIT_H_
#define UNEXPECTEDEXIT_H_

#include "Command.h"
#include "GameManager.h"

class UnexpectedExit: public Command {
public:
	UnexpectedExit(GameManager *info);
	virtual ~UnexpectedExit();
	void setArgs(vector<string> args, int socket);
	bool execute();
private:
	GameManager *info;
	int target;
	SocketHandler *handler;
};

#endif /* UNEXPECTEDEXIT_H_ */
