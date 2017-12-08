#ifndef PLAYERREMOTE_H_
#define PLAYERREMOTE_H_
#include "Player.h"
using namespace std;
/*
 * A remote player that you connect to using a server.
 */
class PlayerRemote : public Player {
public:
	PlayerRemote();
	PlayerRemote(int player_color);
	virtual ~PlayerRemote();
	int GetMove(int* moves);
	void setColor(int player_color);
	int PrintActions();
	void AcknowledgeMove(int x, int y);
private:
	int color;
};
#endif /* PLAYERREMOTE_H_ */
