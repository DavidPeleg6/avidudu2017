/*
 * PlayerAI.h
 *
 *  Author: Avihai Didi
 *  ID: 313137846
 */

#ifndef PLAYERAI_H_
#define PLAYERAI_H_
#include <iostream>
#include "Player.h"
#include "Rules.h"
using namespace std;
/*
 * An AI player that uses a minmax algorithm to choose its moves.
 */
class PlayerAI : public Player {
public:
	PlayerAI(Rules* r);
	virtual ~PlayerAI();
	int GetMove(int* moves);
private:
	Rules* r;
};

#endif /* PLAYERAI_H_ */
