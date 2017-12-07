#include <iostream>
#include <climits>
#include "PlayerHumanLocal.h"
using namespace std;
/**
 * Constructor, does nothing as there is no need for PHL to maintain any data.
 */
PlayerHumanLocal::PlayerHumanLocal() { }
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
