#ifndef PLAYERHUMANLOCAL_H_
#define PLAYERHUMANLOCAL_H_
#include <iostream>
#include "Player.h"
using namespace std;
/**
 * A type of player whose input is acquired trough a local keyboard.
 */
class PlayerHumanLocal : public Player {
public:
	PlayerHumanLocal();
	virtual ~PlayerHumanLocal();
	int GetMove(int* moves);
	int PrintActions();
};

#endif /* PLAYERHUMANLOCAL_H_ */
