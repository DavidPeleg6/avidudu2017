/*
 * Rules.h
 *
 *  Author: Avihai Didi
 *  ID: 313137846
 */

#ifndef RULES_H_
#define RULES_H_
#include <iostream>
#include "Board.h"
using namespace std;
/*
 * This class determines what moves are possible and what constitutes a victory.
 */
class Rules {
	Board* board;
public:
	Rules(Board* game_board);
	virtual ~Rules();
	int* PossibleMoves(int turn);
	int* CheckBoardState();
	int CrawlCheck(int color, int x, int y, int direction);
private:
	int CheckSpot(int color, int x, int y);
	int InBoard(int x, int y);
	int NotOverlap(int x, int y);
};

#endif /* RULES_H_ */
