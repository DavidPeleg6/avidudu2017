/*
 * the interface for commands
 * all commands should inherit from this interface
 */

#ifndef HEADERSS_COMMAND_H_
#define HEADERSS_COMMAND_H_

#include <vector>
#include <string>
#include "SocketHandler.h"

using namespace std;

class Server;

class Command {
public:
	virtual void setArgs(vector<string> args, int socket) = 0;
	virtual bool execute() = 0;
	virtual ~Command() {}

};

#endif /* HEADERSS_COMMAND_H_ */
