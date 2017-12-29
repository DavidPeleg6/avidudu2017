#include "headers/ConsoleDisplay.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "headers/Board.h"
using namespace std;
#define BUFFER_SIZE 225
#define LONGEST_INPUT 11
/*
 * Constructor, does nothing as there is no need for CD to maintain any data.
 */
ConsoleDisplay::ConsoleDisplay() { }
/*
 * Destructor, does nothing as there is no need for CD to maintain any data.
 */
ConsoleDisplay::~ConsoleDisplay() { }
void ConsoleDisplay::WaitForOpponent() {
	cout << "waiting for opponent..." << endl;
}
/*
 * Lets the user choose a move to perform, was originally incorrectly located in PlayerHumanLocal.
 * @param moves - the move list
 * @return the desired index. -1 if the choice made was not in the list.
 * -2 if the input format was invalid.
 */
int ConsoleDisplay::GetMove(int* moves) {
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
 * Informs the user that a game with the name they've chosen already exists.
 */
void ConsoleDisplay::GameAlreadyExists() {
	cout << "A game with that name already exists, please choose a diffrent name." << endl;
}
/*
 * Informs the user that a game with the name they've chosen doesn't exist.
 */
void ConsoleDisplay::GameDoesntExist() {
	cout << "A game with that name doesn't exist, please choose a diffrent name." << endl;
}
/*
 * Asks the user to choose a command for the remote server and returns it.
 * Checks that the command is valid before doing so.
 * Note, the address returned must be freed.
 * @return - a pointer to the user input.
 */
char* ConsoleDisplay::GetClientCommand() {
	//I assumed the users input will be shorter than BUFFER_SIZE letters.
	char* buffer = (char*)malloc(BUFFER_SIZE * sizeof(char));
	char* inchk = (char*)malloc(LONGEST_INPUT * sizeof(char));
	char* output;
	int i, valid_input = 0;
	cout << "Please input one of the following commands:" << endl;
	cout << "list_games\tReturns a list of games you can join." << endl;
	cout << "join <name>\tJoin a game called <name>." << endl;
	cout << "start <name>\tStart a new game called <name> that other";
	cout << " players will be able to join." << endl;
	cin >> buffer;
	while (valid_input == 0) {
		//check that the given input is actually one of the commands.
		i = 0;
		while (buffer[i] != '\0' && buffer[i] != ' ' && i < LONGEST_INPUT) {
			i++;
		}
		for (int j = 0; j <= i; j++) {
			inchk[j] = buffer[j];
		}
		if (strcmp(inchk, "list_games") == 0) {
			valid_input = 2;
		}
		if (strcmp(inchk, "join") == 0 || strcmp(inchk, "start") == 0) {
			valid_input = 1;
		}
		if (valid_input == 1) {
			//get the parameter
			cin >> buffer;
		} else if (valid_input == 0) {
			cout << "Invalid input, please choose one of the commands listed above." << endl;
			cin >> buffer;
			free(inchk);
			inchk = (char*)calloc(LONGEST_INPUT, sizeof(char));
		} else {
			output = inchk;
		}
	}
	if (valid_input == 1) {
		int paramlen = 0;
		while (buffer[paramlen++] != '\0');
		output = (char*)malloc(sizeof(char) * (2 + i + paramlen));
		for (int o = 0; o < i; o++) {
			output[o] = inchk[o];
		}
		output[i] = ' ';
		for (int o = 0; o < paramlen; o++) {
			output[i + 1 + o] = buffer[o];
		}
		free(inchk);
	}
	free(buffer);
	return output;
}
/*
 * Notify the user that the server has crashed.
 */
void ConsoleDisplay::ServerCrash() {
	cout << "A server error has occured, closing game." << endl;
}
/*
 * Gets a list of pointers to strings and prints them.
 * The first string is actually just a byte containing the size of the rest of the list.
 * IT ALSO FREES THE MEMORY.
 * @param games - a pointer to a list of pointers to strings.
 */
void ConsoleDisplay::PrintGameList(char** games) {
	int listsize = games[0][0];
	cout << "The avilable games are:" << endl;
	for (int i = 1; i < listsize + 1; i++) {
		cout << games[i] << endl;
		free(games[i]);
	}
	free(games[0]);
	free(games);

}
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
	cout << "Please enter your move row,col:" << endl;
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
}
/*
 * States what action the player in question took.
 * @param x - the x coordinate
 * @param y - the y coordinate
 * @param player - the color of the player making the move.
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
/*
 * Asks the user for input on what kind of players it would like.
 * @param playerNum - the number of the player being asked for,
 *  if it equals -1 it means the number is irrelevent.
 * @return the value chosen.
 */
int ConsoleDisplay::AskForPlayer(int playerNum) {
	int input;
	if (playerNum == -1) {
		cout << "Please choose your opponent:";
	} else {
		cout << "Please choose player:";
		if (playerNum == 1) {
			cout << "O";
		} else if (playerNum == 2) {
			cout << "X";
		} else {
			cout << "ERROR";
		}
	}
	cout << " (AI = 1 , player = 2, remote player = 3)" << endl;
	cin >> input;
	return input;
}
/*
 * Informs the player that they've made an invalid choice.
 */
void ConsoleDisplay::InvalidChoice() {
	cout << "Invalid choice, please input a diffrent choice." << endl;
}
/*
 * Tells the player to wait for the other player to make a move.
 */
void ConsoleDisplay::WaitForOtherPlayer() {
	cout << "Please wait for the other player to finish their turn." << endl;
}
