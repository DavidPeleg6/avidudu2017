#ifndef PLAYERHUMANLOCAL_H_
#define PLAYERHUMANLOCAL_H_
#include "Player.h"
#include "Display.h"
using namespace std;
/**
 * A type of player whose input is acquired trough a local keyboard.
 */
class PlayerHumanLocal : public Player {
public:
	PlayerHumanLocal(int color, Display* display);
	virtual ~PlayerHumanLocal();
	int GetMove(int* moves);
	int PrintActions();
	void AcknowledgeMove(int x, int y);
	int getColor();
private:
	int player_color;
	Display* d;

};

#endif /* PLAYERHUMANLOCAL_H_ */
