#include <iostream>
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
			p[1] = new PlayerRemote(reader->ExtractIP(data), reader->ExtractPort(data));
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
	delete b;
	delete d;
	delete p[0];
	delete p[1];
	delete r;
	delete g;
	return 0;
}
