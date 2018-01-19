/*
 * SocketHandler.h
 */

#ifndef SOCKETHANDLER_H_
#define SOCKETHANDLER_H_

#define ERROR 0
#include <unistd.h>

class SocketHandler {
public:
	SocketHandler();
	virtual ~SocketHandler();
	int passInt(int clientSocket, int num);
	int passString(int clientSocket, int stringSize, const char* message);
	char* getString(int clientSocket);
};

#endif /* SOCKETHANDLER_H_ */
