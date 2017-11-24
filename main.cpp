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
	PlayerHumanLocal* p1 = new PlayerHumanLocal();
	PlayerHumanLocal* p2 = new PlayerHumanLocal();
	Rules* r = new Rules(b);
	Game* g = new Game(b, r);
	g->RunGame(p1, p2, d);
	delete b;
	delete d;
	delete p1;
	delete p2;
	delete r;
	delete g;
	return 0;
}
