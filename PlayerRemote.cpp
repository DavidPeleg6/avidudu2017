#include "headers/PlayerRemote.h"

using namespace std;
/*
 * Constructor, does nothing.
 */
PlayerRemote::PlayerRemote() {
	color = 0;
}
/*
 * Constructor, tells the player what color it is.
 * @param player_color the color.
 */
PlayerRemote::PlayerRemote(int player_color) {
	color = player_color;
}
/*
 * Destructor, does nothing.
 */
PlayerRemote::~PlayerRemote() { }
int PlayerRemote::GetMove(int* moves) {
	//TODO get the move from the server
	return 0;
}
void PlayerRemote::setColor(int player_color) {
	color = player_color;
}
/*
 * Returns 1, because this type of player requires visual output.
 */
int PlayerRemote::PrintActions() {
	return 1;
}
/*
 * Sends the move the other player did to this player object.
 * Sends the move up to the server.
 */
void PlayerRemote::AcknowledgeMove(int x, int y) {
	//TODO send move to the server.
}
