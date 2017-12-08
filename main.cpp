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

#define AI 1
#define HUMAN 2
#define REMOTE 3
#define BOARDSIZE 8
#define DATAFILE "ipfile"
/*
 * Main function of the program.
 */
int main() {
	FileReader* reader = new FileReader(DATAFILE);
	int* data = reader->read();
	for (int i = 0; i < 5; i++) {
		cout << data[i] << endl;
	}
	cout << "aaa" << endl;
	cout << reader->ExtractIP(data) << endl;
	cout << "aaa" << endl;
	return 0;
	Board* b = new Board(BOARDSIZE, BOARDSIZE);
	b->SetUpGame();
	Display* d = new ConsoleDisplay();
	Rules* r = new Rules(b);
	Player *p[2];
	int remote = 0, input;
	for(int i = 1; i <= 2; i++) {
		d->AskForPlayer(i);
		cin >> input;
		switch (input) {
		case AI:
			p[i - 1] = new PlayerAI(r, b, i);
			break;
		case HUMAN:
			p[i - 1] = new PlayerHumanLocal();
			break;
		case REMOTE:
			if (!remote) {
				p[i - 1] = new PlayerRemote("", 0);
				//TODO propery form a remote player.
				remote = 1;
			} else {
				d->InvalidChoice();
			}
			break;
		default:
			d->InvalidChoice();
			i--;
			break;
		}
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
