#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "headers/Board.h"
#include "headers/ConsoleDisplay.h"
#include "headers/PlayerHumanLocal.h"
#include "headers/PlayerAI.h"
#include "headers/Rules.h"
#include "headers/Game.h"
#include "headers/FileReader.h"
#include "headers/PlayerRemote.h"
using namespace std;

#define BOARDSIZE 8
#define DATAFILE "ipfile"

enum play{NONE, AI, HUMAN, REMOTE};

/*
 * Main function of the program.
 */
int main() {
	FileReader* reader = new FileReader(DATAFILE);
	int* data = reader->read();
	char* ip;
	int ip_set = 0;
	Board* b = new Board(BOARDSIZE, BOARDSIZE);
	b->SetUpGame();
	Display* d = new ConsoleDisplay();
	Rules* r = new Rules(b);
	Player *p[2];
	p[0] = new PlayerHumanLocal(1, d);
	int input = d->AskForPlayer(-1);
	switch (input) {
	case AI:
		p[1] = new PlayerAI(r, b, 2);
		break;
	case HUMAN:
		p[1] = new PlayerHumanLocal(2, d);
		break;
	case REMOTE:
		PlayerRemote *player_remote;
		try {
			if (data[0] == -1) {
				throw "Ip data file error.";
			}
			ip = reader->ExtractIP(data);
			ip_set = 1;
			player_remote = new PlayerRemote(ip, reader->ExtractPort(data));
		} catch (const char *msg) {
			cout << "unnable to connect because: " << msg << endl;
		}
		//TODO user command stuff
		char* command;
		int server_response, interacting_with_server;
		interacting_with_server = 1;
		Client* client;
		client = player_remote->getClient();
		while (interacting_with_server) {
			command = d->GetClientCommand();
			if (strcmp(command, "list_games") == 0) {
				d->PrintGameList(client->listGames(command));
			} else {
				server_response = client->passSimpleCommand(command);
				//TODO all should return the negation of their value if they fail
				//start should return 1
				//join should return 2
				//close should return 3
				switch (server_response) {
				case -1:
					d->GameAlreadyExists();
					break;
				case -2:
				case -3:
					d->GameDoesntExist();
					break;
				case 1:
					//Started a game, wait for other player.
					player_remote->setColor(2);
					d->WaitForOpponent();
					free(command);
					command = (char*)malloc(sizeof(char) * 8);
					command[0] = 'w';
					command[1] = 'a';
					command[2] = 'i';
					command[3] = 't';
					command[4] = 'i';
					command[5] = 'n';
					command[6] = 'g';
					command[7] = '\0';
					server_response = client->passSimpleCommand(command);
					//TODO maybe do something with the response
					interacting_with_server = 0;
					break;
				case 2:
					//Joined a game.
					player_remote->setColor(1);
					interacting_with_server = 0;
					break;
				case 3:
					//Closed a game, do nothing.
					break;
				default:
					d->ServerCrash();
					break;
				}
			}
			free(command);
		}
		p[1] = player_remote;
		break;
	default:
		d->InvalidChoice();
		break;
	}
	Game* g = new Game(b, r, p[0], p[1]);
	try {
		g->RunGame(d);
	} catch (const char* msg) {
		cout << msg << endl;
	}
	if (data[0] != -1 && ip_set) {
		free(ip);
	}
	free(data);
	delete reader;
	delete b;
	delete d;
	delete p[0];
	delete p[1];
	delete r;
	delete g;
	return 0;
}
