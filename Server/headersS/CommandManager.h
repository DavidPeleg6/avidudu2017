/*
 * a class responsible for managing commands = we will add new commands to this class as we make them
 * server will use this class for executing commands given by clients or users
 */
#ifndef SERVEREX5_HEADERSS_COMMANDMANAGER_H_
#define SERVEREX5_HEADERSS_COMMANDMANAGER_H_

#include "Server.h"
#include "Command.h"
#include "PrintListCommand.h"
#include "GameManager.h"
#include <map>
#include <iostream>
#include <sstream>

class CommandManager {
public:
	CommandManager();
	~CommandManager();
	void executeCommand(char* commandMsg);
	void killServer(Server server);

private:
	map<string, Command*> commandsMap;
	GameManager manager;
	vector<string> stringParse(string commandMsg);
};



#endif /* SERVEREX4_HEADERSS_COMMANDMANAGER_H_ */
