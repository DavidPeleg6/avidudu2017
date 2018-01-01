#include "headers/PlayerHumanLocal.h"
#include "headers/Display.h"


//todo delete
#include <stdio.h>
#include <time.h>
#include <unistd.h>



using namespace std;
/**
 * Constructor, gives the player their color.
 */
PlayerHumanLocal::PlayerHumanLocal(int color, Display* display) {
	player_color = color;
	d = display;
}
/**
 * Destructor, also does nothing.
 */
PlayerHumanLocal::~PlayerHumanLocal() { }
/*
 * Returns 1, because this type of player requires visual output.
 */
int PlayerHumanLocal::PrintActions() {
	return 1;
}
/*
 * Returns the index of the desired move in the movelist.
 * @param moves - the move list
 * @return the desired index. -1 if the choice made was not in the list.
 * -2 if the input format was invalid.
 * (actually just calls the function in Display)
 */
int PlayerHumanLocal::GetMove(int* moves) {
	return d->GetMove(moves);
}
/*
 * Returns the color of this player.
 * @return the color of this player.
 */
int PlayerHumanLocal::getColor() {
	return player_color;
}
/*
 * Sends the move the other player did to this player object.
 * Doesn't do anything.
 */
void PlayerHumanLocal::AcknowledgeMove(int x, int y) { }
