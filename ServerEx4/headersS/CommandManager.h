/*
 * a class responsible for managing commands = we will add new commands to this class as we make them
 * server will use this class for executing commands given by clients or users
 */
#ifndef SERVEREX4_HEADERSS_COMMANDMANAGER_H_
#define SERVEREX4_HEADERSS_COMMANDMANAGER_H_

#include <map>
#include "Command.h"

class CommandManager {
public:
	CommandManager();
	~CommandManager();
	void executeCommand(string command, vector<string> args);

private:
	map<string, Command *> commandsMap;
};



#endif /* SERVEREX4_HEADERSS_COMMANDMANAGER_H_ */
