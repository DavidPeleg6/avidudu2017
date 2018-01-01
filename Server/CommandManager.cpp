#include "headersS/CommandManager.h"

using namespace std;

/*
 * command manager constructor
 * creates and fills map
 */
CommandManager::CommandManager() {
	manager = new GameManager();
	//add commands in the following format
	commandsMap["list_games"] = new PrintListCommand(manager);
	commandsMap["exit"] = new killServerCommand(manager);
	commandsMap["close"] = new CloseGameCommand(manager);
	commandsMap["start"] = new StartGameCommand(manager);
	commandsMap["join"] = new JoinGameCommand(manager);
	commandsMap["play"] = new PlayCommand(manager);
}

/*
 * get command method
 * will get string and return the appropriate command from the list of keys in map
 */
Command* CommandManager::getCommand(const char* commandMsg, int socket) {
	string str(commandMsg);
	//parse string to command and param
	vector<string> parsed = stringParse(commandMsg);
	//get command name
	Command *command = commandsMap[parsed.front().c_str()];
	if (command == NULL) {
		cout << "Unknown command." << endl;
		return NULL;
	}
	//Command *command =new StartGameCommand(manager);
	parsed.erase(parsed.begin());
	command -> setArgs(parsed, socket);
	return command;
}

/*
 * destructor- deleting all objects from map
 */
CommandManager::~CommandManager() {
	map<string, Command *>::iterator it;
	for(it = commandsMap.begin(); it != commandsMap.end(); it++) {
		delete it -> second;
	}
	delete manager;
}

/*
 * stringParse method returns a vector of arguments and the command key at the top
 */
vector<string> CommandManager::stringParse(string commandMsg) {
	vector<string> parsed;
	istringstream buf(commandMsg);
	string temp;
	while (getline(buf,temp,' ')) {
		parsed.push_back(temp);
	}
	return parsed;
}
