/*
 * PlayerAI.cpp
 *
 *  Author: Avihai Didi
 *  ID: 313137846
 */

#include "PlayerAI.h"
#include "Rules.h"
#include "Board.h"
#include <climits>
/*
 * Constructor, just gives it the rules-et it'll need to make decisions.
 */
PlayerAI::PlayerAI(Rules* rules, Board* board) {
	r = rules;
	b = board;
}
/*
 * Destructor, does nothing.
 */
PlayerAI::~PlayerAI() { }

int PlayerAI::GetMove(int* moves) {
	int score;
	int min_enemy_score = INT_MIN;
	int min_enemy_score_move = 1;
	if (moves[0] == 1) {
		return min_enemy_score_move;
	}
	for (int i = 1; i < moves[0] ; i+= 2) {
		Board* sim_board = b->SimBoard();
		Rules* sim_rules = r->CopyRules(sim_board);
		score = 0; //TODO get board score, and simulate it.
		if (score < min_enemy_score) {
			min_enemy_score = score;
			min_enemy_score_move = i;
		}
		delete sim_board;
		delete sim_rules;
	}
	return min_enemy_score_move;
}
int PlayerAI::BestMove(int* moves, Board* board) {

}
