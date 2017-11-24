/*
 * Game.h
 *
 *  Author: Avihai Didi
 *  ID: 313137846
 */

#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include "Player.h"
#include "Display.h"
#include "Board.h"
#include "Rules.h"
using namespace std;
/*
 * Manages the game itself, uses the Rules class to determine what moves are
 *  possible and then gets moves from player objects and determines using the
 *   Rules class how those moves should affect the game.
 */
class Game {
	Board* board;
	Rules* rules;
public:
	Game(Board* b, Rules* r);
	virtual ~Game();
	void RunGame(Player* p1, Player* p2, Display* d);
private:
	void SetPiece(int color, int x, int y);
	void Crawl(int color, int x, int y, int direction, int amount);
};

#endif /* GAME_H_ */
