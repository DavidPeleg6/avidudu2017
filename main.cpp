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
/**
 * Main function of the program.
 */
int main() {
	Board* b = new Board(8, 8);
	b->SetUpGame();
	ConsoleDisplay* d = new ConsoleDisplay();
	Rules* r = new Rules(b);
	PlayerAI* p1 = new PlayerAI(r, b, 1);
	PlayerAI* p2 = new PlayerAI(r, b, 2);
	Game* g = new Game(b, r, p1, p2);
	g->RunGame(d);
	delete b;
	delete d;
	delete p1;
	delete p2;
	delete r;
	delete g;
	return 0;
}
