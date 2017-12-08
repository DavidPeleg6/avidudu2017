#include "headers/PlayerRemote.h"
#include "headers/Client.h"
#include <stdlib.h>

using namespace std;
/*
 * Constructor, starts the client and recieves the color.
 */
PlayerRemote::PlayerRemote(const char *serverIP, int serverPort) {
	player_color = 0;
	client = new Client(serverIP, serverPort);
	//set remote player with the opposite color
	setColor(3 - client->connectToServer());
}
/*
 * Destructor, deletes client.
 */
PlayerRemote::~PlayerRemote() {
	delete client;
}
/*
 * Gets a move from the remote player.
 * @param moves - the list of possible moves,
 * the other player should have the game list.
 * @return the index of the chosen move.
 */
int PlayerRemote::GetMove(int* moves) {
	int* move = client->GetMove();
	for (int i = 1; i < moves[0] ; i+= 2) {
		if (moves[i] == move[0] && moves[i + 1] == move[1]) {
			free(move);
			return i;
		}
	}
	free(move);
	return -1;
}
/*
 * Sets the color of this player.
 * @param color - the color to be set.
 */
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
 * Sends the move just made to the other player.
 * @param x - the x coordinate
 * @param y - the y coordinate
 * @param color - the color of the player making the move.
 */
void PlayerRemote::AcknowledgeMove(int x, int y, int color) {
	client->SendMove(x, y, color);
}
