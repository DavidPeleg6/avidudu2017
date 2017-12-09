#include <iostream>
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
	int input;
	p[0] = new PlayerHumanLocal(1);
	d->AskForPlayer(-1);
	cin >> input;
	switch (input) {
	case AI:
		p[1] = new PlayerAI(r, b, 2);
		break;
	case HUMAN:
		p[1] = new PlayerHumanLocal(2);
		break;
	case REMOTE:
		try {
			if (data[0] == -1) {
				throw "Ip data file error.";
			}
			ip = reader->ExtractIP(data);
			ip_set = 1;
			p[1] = new PlayerRemote(ip, reader->ExtractPort(data));
		} catch (const char *msg) {
			cout << "unnable to connect because: " << msg << endl;
		}
		break;
	default:
		d->InvalidChoice();
		break;
	}
	Game* g = new Game(b, r, p[0], p[1]);
	g->RunGame(d);
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
