/*
 * Game.cpp
 *
 *  Author: Avihai Didi
 *  ID: 313137846
 */
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Display.h"
#include "Board.h"
#include "Rules.h"
using namespace std;
/*
 * Constructor, adds references to the board the game will be played on and
 *  the rules that will be used to determine the way the game behaves.
 *  @param b - the board the game will be played on.
 *  @param r - the rules that judge the behavior of the game.
 */
Game::Game(Board* b, Rules* r) {
	board = b;
	rules = r;
}
/**
 * Destructor, doesn't do anything as the
 *  board and rules may be used elsewhere in the program.
 */
Game::~Game() { }
/*
 * The main function of the whole program. Manages the actual game.
 * @param p1 - Class that controls the black pieces.
 * @param p2 - Class that controls the white pieces.
 * @param d - Outputs the state of the game visually.
 */
void Game::RunGame(Player* p1, Player* p2, Display* d) {
	int move, turn = 1;
	int no_move_flag = 0;
	int* moves;
	int* state = rules->CheckBoardState();
	while (state[0] == 0) {
		turn = 3 - turn;
		move = -1;
		moves = rules->PossibleMoves(turn);
		d->Print(board, turn, moves);
		if (moves[0] == 0) {
			//no possible moves, switch to other player.
			if (no_move_flag == 0) {
				no_move_flag = 1;
			} else {
				delete moves;
				delete state;
				break;
			}
		} else {
			no_move_flag = 0;
			while (move == -1) {
				d->AskForMove();
				if (turn == 1) {
					move = p1->GetMove(moves);
				} else {
					move = p2->GetMove(moves);
				}
				if (move == -1) {
					d->InvalidMove();
				}
				if (move == -2) {
					d->InvalidFormat();
					move = -1;
				}
			}
			rules->SetPiece(turn, moves[move], moves[move + 1]);
		}
		delete moves;
		delete state;
		state = rules->CheckBoardState();
	}
	if (no_move_flag == 0) {
		d->PrintBoard(board);
	}
	d->DeclareWinner(state);
}

