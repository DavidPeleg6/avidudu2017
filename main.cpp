#include <iostream>
#include "headers/Board.h"
#include "headers/ConsoleDisplay.h"
#include "headers/PlayerHumanLocal.h"
#include "headers/PlayerAI.h"
#include "headers/Rules.h"
#include "headers/Game.h"
#include "headers/FileReader.h"
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
	Board* b = new Board(BOARDSIZE, BOARDSIZE);
	b->SetUpGame();
	Display* d = new ConsoleDisplay();
	Rules* r = new Rules(b);
	Player *p[2];
	int player;
	for(int i = 1; i <= 2; i++) {
		d->AskForPlayer();
		cin >> player;
		switch (player) {
		case AI:
			p[i - 1] = new PlayerAI(r, b, i);
			break;
		case HUMAN:
			p[i - 1] = new PlayerHumanLocal();
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
