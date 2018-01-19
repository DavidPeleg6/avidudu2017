#ifndef GAME_H_
#define GAME_H_
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
	Player* p1;
	Player* p2;
public:
	Game(Board* b, Rules* r, Player* p1, Player* p2);
	virtual ~Game();
	void RunGame(Display* d);
	Player* GetPlayer(int player);
};

#endif /* GAME_H_ */
