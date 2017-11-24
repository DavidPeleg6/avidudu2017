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
	void SetPiece(int color, int x, int y);
	Rules* CopyRules(Board* game_board);
	int bestScore(int player);
private:
	int CheckSpot(int color, int x, int y);
	int InBoard(int x, int y);
	int NotOverlap(int x, int y);
	void Crawl(int color, int x, int y, int direction, int amount);
	int CrawlCheck(int color, int x, int y, int direction);
};

#endif /* RULES_H_ */
