/*
 * main.cpp
 *
 *  Author: Avihai Didi
 *  ID: 313137846
 */
#include <iostream>
#include "Board.h"
#include "ConsoleDisplay.h"
#include "PlayerHumanLocal.h"
#include "PlayerAI.h"
#include "Rules.h"
#include "Game.h"
using namespace std;

#define AI 1
#define HUMAN 2
/**
 * Main function of the program.
 */
int main() {
	Board* b = new Board(8, 8);
	b->SetUpGame();
	Display* d = new ConsoleDisplay();
	Rules* r = new Rules(b);
	Player *p[2];
	int player;
	for(int i = 1; i <= 2; i++) {
		d->AskForPlayer(i);
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
