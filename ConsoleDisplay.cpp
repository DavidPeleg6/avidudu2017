#include "ConsoleDisplay.h"
#include <iostream>
#include <stdlib.h>
#include "Board.h"
using namespace std;
/*
 * Constructor, does nothing as there is no need for CD to maintain any data.
 */
ConsoleDisplay::ConsoleDisplay() { }
/*
 * Destructor, does nothing as there is no need for CD to maintain any data.
 */
ConsoleDisplay::~ConsoleDisplay() { }
/**
 * Prints a list of possible moves the player can make.
 * @param moves - a list of cords, assumed to be 1 + even.
 */
void ConsoleDisplay::PrintMoves(int* moves) {
	if (moves[0] == 0) {
		//no possible moves, switch to other player
		cout << "No possible moves. Play passes back to";
		cout <<" the other player. Press any key to continue." << endl;
		cin.ignore();
	} else {
		cout << "Your possible moves: ";
		for (int i = 1; i < moves[0] ; i+= 2) {
			cout << "(" << moves[i] << "," << moves[i + 1] << ") ";
		}
		cout << endl;
	}
}
/**
 * Prints a blank line of dashes.
 * @param b - the board.
 */
void ConsoleDisplay::PrintDashLine(Board* b) {
	for (int i = 0; i < (b->getWidth() * 2) + 1; i++) {
		cout << "--";
	}
	cout << endl;
}
/**
 * Prints the current board.
 * @param b - the board.
 */
void ConsoleDisplay::PrintBoard(Board* b) {
	for (int i = 1; i < b->getWidth() + 1; i++) {
		cout << " | " << i;
	}
	cout << " |" << endl;
	PrintDashLine(b);
	for (int j = 1; j <= b->getHeight(); j++) {
		cout << j << "| ";
		for (int i = 1; i <= b->getWidth(); i++) {
			switch (b->get(i, j)) {
				case 0:
					cout << " ";
					break;
				case 1:
					cout << "O";
					break;
				case 2:
					cout << "X";
					break;
				default:
					cout << "E";
					break;
			}
			cout << " | ";
		}
		cout << endl;
		PrintDashLine(b);
	}
}
/*
 * Asks the player for a move.
 */
void ConsoleDisplay::AskForMove() {
	cout << "Please enter your move row,col: ";
}
/*
 * Tells the player that the move they chose is invalid.
 */
void ConsoleDisplay::InvalidMove() {
	cout << "Invalid move, please choose another move" << endl;
}
/*
 * Tells the player that the input format was incorrect.
 */
void ConsoleDisplay::InvalidFormat() {
	cout << "Invalid input format, please input two integers separated by";
	cout <<	" a single character, preferably a comma." << endl;
}
/*
 * Prints the current state of the board and other data.
 * @paran b - the board to be printed.
 * @paran turn - the player whose turn it is.
 * @paran moves - the moves available to the player.
 */
void ConsoleDisplay::Print(Board* b, int turn, int* moves) {
	cout << "Current board:" << endl;
	cout << endl;
	PrintBoard(b);
	PrintTurn(turn);
	PrintMoves(moves);
}
/*
 * Prints whose turn it is.
 * @param turn - the turn indicator.
 */
void ConsoleDisplay::PrintTurn(int turn) {
	if (turn == 1) {
		cout << "O";
	} else {
		cout << "X";
	}
	cout << ": It's your move." << endl;
}
/*
 * Declares who the winner of the game is.
 * @param state - the winner, number of O and number of X.
 */
void ConsoleDisplay::DeclareWinner(int* state) {
	cout << "0: " << state[1] << endl;
	cout << "X: " << state[2] << endl;
	switch (state[0]) {
		case 0:
			cout << "Game over, an early victory for player: ";
			if (state[2] > state[1]) {
				cout << "X!" << endl;
			} else {
				cout << "O!" << endl;
			}
			break;
		case 1:
			cout << "Game over, player O has won!" << endl;
			break;
		case 2:
			cout << "Game over, player X has won!" << endl;
			break;
		case 3:
			cout << "Game over, it's a tie." << endl;
			break;
		default:
			cout << "Game over, an error has occurred and";
			cout <<	" a winner cannot be determined." << endl;
		break;
	}
	free(state);
}
/*
 * States what action the player in question took.
 */
void ConsoleDisplay::StatePlay(int x, int y, int player) {
	if (player == 1) {
		cout << "O";
	} else if (player == 2) {
		cout << "X";
	} else {
		cout << "ERROR";
	}
	cout << " played (" << x << "," << y << ")" << endl;
}

void ConsoleDisplay::AskForPlayer(int playerNum) {
	cout << "Please choose player ";
	if (playerNum == 1) {
		cout << "O";
	} else if (playerNum == 2) {
		cout << "X";
	} else {
		cout << "ERROR";
	}
	cout << " (AI = 1 , player = 2)" << endl;
}
