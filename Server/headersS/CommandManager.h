/*
 * a class responsible for managing commands = we will add new commands to this class as we make them
 * server will use this class for executing commands given by clients or users
 */
#ifndef SERVEREX4_HEADERSS_COMMANDMANAGER_H_
#define SERVEREX4_HEADERSS_COMMANDMANAGER_H_

#include "Command.h"
#include "PrintListCommand.h"
#include "Server.h"
#include <map>
#include <iostream>
#include <sstream>

class CommandManager {
public:
	CommandManager();
	~CommandManager();
	void executeCommand(char* commandMsg);
	void killAllGames();

private:
	map<string, Command*> commandsMap;
	vector<string> stringParse(string commandMsg);
};



#endif /* SERVEREX4_HEADERSS_COMMANDMANAGER_H_ */
