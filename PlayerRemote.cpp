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
	setColor(client->connectToServer());
}
/*
 * Destructor, deletes client.
 */
PlayerRemote::~PlayerRemote() {
	delete client;
}

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
	client->SendMove(x, y, color);
}
