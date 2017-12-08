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
	PlayerHumanLocal(int color);
	virtual ~PlayerHumanLocal();
	int GetMove(int* moves);
	int PrintActions();
	void AcknowledgeMove(int x, int y, int color);
	int getColor();
private:
	int player_color;
};

#endif /* PLAYERHUMANLOCAL_H_ */
