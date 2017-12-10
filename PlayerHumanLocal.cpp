#include <iostream>
#include <climits>
#include "headers/PlayerHumanLocal.h"
using namespace std;
/**
 * Constructor, gives the player their color.
 */
PlayerHumanLocal::PlayerHumanLocal(int color) {
	player_color = color;
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
 */
int PlayerHumanLocal::GetMove(int* moves) {
	//return 1; //highly advanced debugging tool
	int x, y, sx, sy;
	char comma;
	if (cin.peek() == '\n') {
		cin.ignore();
	}
	if (!isdigit(cin.peek())) {
		do {
			cin.ignore();
		} while (cin.peek() != '\n');
		return -2;
	}
	cin >> x;
	cin >> comma;
	if (!isdigit(cin.peek())) {
		do {
			cin.ignore();
		} while (cin.peek() != '\n');
		return -2;
	}
	cin >> y;
	for (int i = 1; i < moves[0] ; i+= 2) {
		sx = moves[i];
		sy = moves[i + 1];
		if (sx == x && sy == y) {
			return i;
		}
	}
	return -1;
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
void PlayerHumanLocal::AcknowledgeMove(int x, int y, int color) { }
