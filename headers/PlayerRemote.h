#ifndef PLAYERREMOTE_H_
#define PLAYERREMOTE_H_
#include "Player.h"
#include "Client.h"
using namespace std;
/*
 * A remote player that you connect to using a server.
 */
class PlayerRemote : public Player {
public:
	PlayerRemote(const char *serverIP, int serverPort);
	PlayerRemote(const char *serverIP, int serverPort, int color);
	virtual ~PlayerRemote();
	int GetMove(int* moves);
	void setColor(int color);
	int getColor();
	int PrintActions();
	void AcknowledgeMove(int x, int y, int color);
private:
	int player_color;
	Client* client;
};
#endif /* PLAYERREMOTE_H_ */
