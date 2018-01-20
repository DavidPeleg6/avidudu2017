#include "headers/PlayerRemote.h"
#include "headers/Client.h"
#include <stdlib.h>
#define END_MESSAGE -2
using namespace std;
/*
 * Constructor, starts the client and recieves the color.
 */
PlayerRemote::PlayerRemote(const char *serverIP, int serverPort) {
	setColor(0); //the actuall color is set at the main
	client = new Client(serverIP, serverPort);
	//set remote player with the opposite color
	try {
		client->connectToServer();
	} catch(const char *msg) {
		cout << msg << endl;
		exit(-1);
	}
}
/*
 * Destructor, deletes client.
 */
PlayerRemote::~PlayerRemote() {
	if (player_color == 2) {
		client->writeCommand("close", 6);
	}
	delete client;
}
/*
 * Returns the client.
 */
Client* PlayerRemote::getClient() {
	return client;
}
/*
 * Gets a move from the remote player.
 * @param moves - the list of possible moves,
 * the other player should have the game list.
 * @return the index of the chosen move.
 * @throws exception if end game was suddenly received from server
 */
int PlayerRemote::GetMove(int* moves) {
	int* move;
	try {
		move = client->GetMove();
	} catch(const char *msg) {
		cout << msg << endl;
		exit(-1);
	}
	if(move[0] == END_MESSAGE) {
		throw "Game has ended due to unexpected server shutdown.";
	}
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
 * Returns the color of this player.
 * @return the color of this player.
 */
int PlayerRemote::getColor() {
	return player_color;
}
/*
 * Returns 2, because this type of player requires
 * visual output of the board but not the possible moves.
 */
int PlayerRemote::PrintActions() {
	return 2;
}
/*
 * Sends the move just made to the other player.
 * @param x - the x coordinate
 * @param y - the y coordinate
 * @param color - the color of the player making the move.
 */
void PlayerRemote::AcknowledgeMove(int x, int y) {
	try {
		client->SendMove(x, y);
		if(x == 0 && y == 0) {
			int *garbage = new int[1];
			GetMove(garbage);
			delete[] garbage;
		}
	} catch(const char *msg) {
		cout << msg << endl;
		exit(-1);
	}
}
