#include "headersS/CommandManager.h"
using namespace std;


CommandManager::CommandManager() {
	//add commands in the following format
	commandsMap["list_games"] = new PrintListCommand();
}

void CommandManager::executeCommand(char* commandMsg) {
	string str(commandMsg);
	//parse string to command and param
	vector<string> parsed = stringParse(commandMsg);
	//get command name
	Command *command = commandsMap[parsed.front()];
	parsed.erase(parsed.begin());
	command -> execute(parsed);
}

CommandManager::~CommandManager() {
	map<string, Command *>::iterator it;
	for(it = commandsMap.begin(); it != commandsMap.end(); it++) {
		delete it -> second;
	}
}

vector<string> CommandManager::stringParse(string commandMsg) {
	vector<string> parsed;
	istringstream buf(commandMsg);
	string temp;
	while (getline(buf,temp,' ')) {
		parsed.push_back(temp);
	}
	return parsed;
}

void CommandManager::killServer(Server server) {
}
