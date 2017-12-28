/*
 * the interface for commands
 * all commands should inherit from this interface
 */

#ifndef SERVEREX4_HEADERSS_COMMAND_H_
#define SERVEREX4_HEADERSS_COMMAND_H_

#include <vector>
#include <string>
using namespace std;

class Command {
public:
	virtual void execute(vector<string> args) = 0;
	virtual ~Command() {}
};

#endif /* SERVEREX4_HEADERSS_COMMAND_H_ */
