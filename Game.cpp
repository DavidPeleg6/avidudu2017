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
			SetPiece(turn, moves[move], moves[move + 1]);
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
/*
 * Places a piece and flips adj pieces according to the rules.
 * It is assumes the place the piece is set in is valid.
 * @param color - the color of the piece being placed.
 * @param x - x cord to be placed at.
 * @param y - y cord to be placed at.
 * @return 0 if the piece couldn't be placed, 1 otherwise.
 */
void Game::SetPiece(int color, int x, int y) {
	board->set(x, y, color);
	//Check all adjacent spaces
	Crawl(color, x, y, 1, rules->CrawlCheck(color, x, y, 1));
	Crawl(color, x, y, 2, rules->CrawlCheck(color, x, y, 2));
	Crawl(color, x, y, 3, rules->CrawlCheck(color, x, y, 3));
	Crawl(color, x, y, 4, rules->CrawlCheck(color, x, y, 4));
	Crawl(color, x, y, 6, rules->CrawlCheck(color, x, y, 6));
	Crawl(color, x, y, 7, rules->CrawlCheck(color, x, y, 7));
	Crawl(color, x, y, 8, rules->CrawlCheck(color, x, y, 8));
	Crawl(color, x, y, 9, rules->CrawlCheck(color, x, y, 9));
}
/*
 * Places a specified amount of pieces in a given direction starting from (x,y).
 * Ignores starting point.
 * Directions are based on the numpad.
 * @param color - the color of the piece being placed.
 * @param x - x cord to be placed at.
 * @param y - y cord to be placed at.
 * @param direction - the direction go travel in.
 * @param amount - the ammout of nodes to flip.
 */
void Game::Crawl(int color, int x, int y, int direction, int amount) {
	int cx = x;
	int cy = y;
	for (int i = 0; i < amount; i++) {
		switch (direction) {
			case 1:
				cx--;
				cy++;
				break;
			case 2:
				cy++;
				break;
			case 3:
				cx++;
				cy++;
				break;
			case 4:
				cx--;
				break;
			case 6:
				cx++;
				break;
			case 7:
				cx--;
				cy--;
				break;
			case 8:
				cy--;
				break;
			case 9:
				cx++;
				cy--;
				break;
			default:
				//do nothing
				break;
		}
		board->set(cx, cy, color);
	}
}
