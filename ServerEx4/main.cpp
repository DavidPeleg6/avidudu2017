/*
 * main.cpp
 * creating the server that runs the game
 * Server will use the IP and port that are mentioned in the ipfile
 */

#include "headersS/Server.h"
#include "headersS/FileReader.h"
#include <stdlib.h>
#define DATAFILE "ipfile"

int main() {
	FileReader* reader = new FileReader(DATAFILE);
	int* data = reader->read();
	Server server(reader->ExtractPort(data));
	try {
		server.start();
	} catch(const char *msg) {
		cout << "server crashed because: " << msg << endl;
		exit(-1);
	}
}
