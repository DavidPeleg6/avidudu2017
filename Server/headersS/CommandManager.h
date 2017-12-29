/*
 * a class responsible for managing commands = we will add new commands to this class as we make them
 * server will use this class for executing commands given by clients or users
 */
#ifndef HEADERSS_COMMANDMANAGER_H_
#define HEADERSS_COMMANDMANAGER_H_

#include "GameManager.h"
#include "PrintListCommand.h"
#include "killServerCommand.h"
#include "CloseGameCommand.h"
#include "StartGameCommand.h"
#include "JoinGameCommand.h"
#include "PlayCommand.h"
#include "Command.h"
#include <map>
#include <iostream>
#include <sstream>

class CommandManager {
public:
	CommandManager();
	~CommandManager();
	Command* getCommand(char* commandMsg, int socket);

private:
	map<string, Command*> commandsMap;
	GameManager *manager;
	vector<string> stringParse(string commandMsg);
};



#endif /* SERVEREX4_HEADERSS_COMMANDMANAGER_H_ */
