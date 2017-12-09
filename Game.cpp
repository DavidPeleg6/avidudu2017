#include <stdlib.h>
#include "headers/Game.h"
#include "headers/Player.h"
#include "headers/Display.h"
#include "headers/Board.h"
#include "headers/Rules.h"
using namespace std;
/*
 * Constructor, adds references to the board the game will be played on and
 *  the rules that will be used to determine the way the game behaves.
 *  @param b - the board the game will be played on.
 *  @param r - the rules that judge the behavior of the game.
 */
Game::Game(Board* b, Rules* r, Player* player1, Player* player2) {
	board = b;
	rules = r;
	if (player2->getColor() == 2) {
		p1 = player1;
		p2 = player2;
	} else {
		p1 = player2;
		p2 = player1;
	}

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
void Game::RunGame(Display* d) {
	int move, turn = 2;
	int no_move_flag = 0;
	int* moves;
	int* state = rules->CheckBoardState();
	while (state[0] == 0) {
		turn = 3 - turn;
		move = -1;
		moves = rules->PossibleMoves(turn);
		if (GetPlayer(turn)->PrintActions() == 1) {
			d->Print(board, turn, moves);
		} else if (GetPlayer(turn)->PrintActions() == 2) {
			d->PrintBoard(board);
		}
		if (moves[0] == 0) {
			//no possible moves, switch to other player.
			if (no_move_flag == 0) {
				no_move_flag = 1;
			} else {
				free(moves);
				free(state);
				break;
			}
		} else {
			no_move_flag = 0;
			while (move == -1) {
				if (GetPlayer(turn)->PrintActions() == 1) {
					d->AskForMove();
				} else if (GetPlayer(turn)->PrintActions() == 2) {
					d->WaitForOtherPlayer();
				}
				if (turn == 1) {
					move = p1->GetMove(moves);
				} else {
					move = p2->GetMove(moves);
				}
				if (move == -1) {
					if (GetPlayer(turn)->PrintActions()) {
						d->InvalidMove();
					}
				}
				if (move == -2) {
					if (GetPlayer(turn)->PrintActions()) {
						d->InvalidFormat();
					}
					move = -1;
				}
			}
			GetPlayer(3 - turn)->AcknowledgeMove(moves[move], moves[move + 1], turn);
			rules->SetPiece(turn, moves[move], moves[move + 1]);
			if (!GetPlayer(turn)->PrintActions()) {
				d->StatePlay(moves[move], moves[move + 1], turn);
			}
		}
		free(moves);
		free(state);
		state = rules->CheckBoardState();
	}
	if (no_move_flag == 0) {
		d->PrintBoard(board);
	}
	d->DeclareWinner(state);
	free(state);
}
/*
 * Returns the player object whose number is the one given.
 * @param player - the index of the player to be returned.
 * @return the requested player object.
 */
Player* Game::GetPlayer(int player) {
	if (player == 1) {
		return p1;
	}
	if (player == 2) {
		return p2;
	}
	//error.
	return 0;
}
