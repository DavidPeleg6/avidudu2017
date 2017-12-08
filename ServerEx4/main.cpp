/*
 * main.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: david
 */

#include "Server.h"
#include <stdlib.h>

int main() {
	Server server(8000);
	try {
		server.start();
	} catch(const char *msg) {
		cout << "server crashed because: " << msg << endl;
		exit(-1);
	}
}
