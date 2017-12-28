#include "headersS/CommandManager.h"

CommandManager::CommandManager() {
	//add commands in the following format
	//commandsMap["command_name"] = new CommandClass();
}

void CommandManager::executeCommand(string command_name, vector<string> args) {
	Command *command = commandsMap[command_name];
	command -> execute(args);
}

CommandManager::~CommandManager() {
	map<string, Command *>::iterator it;
	for(it = commandsMap.begin(); it != commandsMap.end(); it++) {
		delete it -> second;
	}
}
