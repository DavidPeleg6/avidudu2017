/*
 * main.cpp
 * creating the server that runs the game
 * Server will use the IP and port that are mentioned in the ipfile
 */

#include "headersS/Server.h"
#include "headersS/FileReader.h"
#include "headersS/CommandManager.h"
#include <stdlib.h>
#define DATAFILE "ipfile"
/*
 * Starts the server and handles the clients.
 */
int main() {
	FileReader* reader = new FileReader(DATAFILE);
	CommandManager *manager = new CommandManager();
	int* data = reader->read();
	Server server(reader->ExtractPort(data), manager);
	while (1) {
		try {
			server.start();
		} catch(const char *msg) {
			cout << "server closed because: " << msg << endl;
			server.stop();
			delete reader;
			//delete manager; //TODO fix this
			exit(-1);
		}
	}
	delete reader;
	delete manager;
	server.stop();
	return 0;
}
