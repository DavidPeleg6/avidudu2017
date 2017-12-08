#include "headers/PlayerRemote.h"
#include "headers/Client.h"

using namespace std;
/*
 * Constructor, does nothing.
 */
PlayerRemote::PlayerRemote(const char *serverIP, int serverPort) {
	player_color = 0;
	client = new Client(serverIP, serverPort);
}
/*
 * Constructor, tells the player what color it is.
 * @param player_color the color.
 */
PlayerRemote::PlayerRemote(const char *serverIP, int serverPort, int color) {
	player_color = color;
	client = new Client(serverIP, serverPort);
}
/*
 * Destructor, does nothing.
 */
PlayerRemote::~PlayerRemote() { }
int PlayerRemote::GetMove(int* moves) {
	//TODO get the move from the server
	return 0;
}
void PlayerRemote::setColor(int color) {
	player_color = color;
}
/*
 * Returns 1, because this type of player requires visual output.
 */
int PlayerRemote::PrintActions() {
	return 1;
}
/*
 * Sends the move the other player.
 */
void PlayerRemote::AcknowledgeMove(int x, int y, int color) {
	//TODO send move to the server.
}
