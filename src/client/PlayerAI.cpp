#include "headers/PlayerAI.h"
#include "headers/Rules.h"
#include "headers/Board.h"
#include <climits>
#include <stdlib.h>
/*
 * Constructor, just gives it the rules-et it'll need to make decisions.
 */
PlayerAI::PlayerAI(Rules* rules, Board* board, int player_color) {
	r = rules;
	b = board;
	color = player_color;
}
/*
 * Destructor, does nothing.
 */
PlayerAI::~PlayerAI() { }
/*
 * Returns 0, because this type of player doesn't require visual output.
 */
int PlayerAI::PrintActions() {
	return 0;
}
/*
 * Returns the move that the AI player should choose.
 * @param moves - the list of possible moves to choose from.
 * @return the chosen move.
 */
int PlayerAI::GetMove(int* moves) {
	int score;
	int min_enemy_score = INT_MAX;
	int min_enemy_score_move = 1;
	if (moves[0] == 2) {
		return min_enemy_score_move;
	}
	for (int i = 1; i < moves[0] ; i+= 2) {
		Board* sim_board = b->SimBoard();
		Rules* sim_rules = r->CopyRules(sim_board);
		sim_rules->SetPiece(color, moves[i], moves[i + 1]);
		int* sim_moves = sim_rules->PossibleMoves(3 - color);
		score = BestMoveScore(sim_moves, sim_board, sim_rules, 3 - color);
		free (sim_moves);
		if (score < min_enemy_score) {
			min_enemy_score = score;
			min_enemy_score_move = i;
		}
		delete sim_board;
		delete sim_rules;
	}
	return min_enemy_score_move;
}
/*
 * Gets a board and a set of possible moves and returns the one that would net the most points.
 * @moves - a list of possible moves.
 * @board - the board the moves will be used on.
 * @rules - the rules of the game.
 * @player - the color of the player performing the moves.
 * @return - the highest possible score.
 */
int PlayerAI::BestMoveScore(int* moves, Board* board, Rules* rules, int player) {
	if (moves[0] == 0) {
		return INT_MIN;
	}
	int score, max_score = INT_MIN;
	for (int i = 1; i < moves[0] ; i+= 2) {
		Board* sim_board = board->SimBoard();
		Rules* sim_rules = rules->CopyRules(sim_board);
		sim_rules->SetPiece(player, moves[i], moves[i + 1]);
		score = sim_rules->Score(player);
		if (max_score < score) {
			max_score = score;
		}
		delete sim_board;
		delete sim_rules;
	}
	return max_score;
}
/*
 * Returns the color of this player.
 * @return the color of this player.
 */
int PlayerAI::getColor() {
	return color;
}
/*
 * Sends the move the other player did to this player object.
 * Doesn't do anything.
 */
void PlayerAI::AcknowledgeMove(int x, int y) { }
