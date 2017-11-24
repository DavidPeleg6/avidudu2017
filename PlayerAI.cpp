/*
 * PlayerAI.cpp
 *
 *  Author: Avihai Didi
 *  ID: 313137846
 */

#include "PlayerAI.h"
#include "Rules.h"
/*
 * Constructor, just gives it the rules-et it'll need to make decisions.
 */
PlayerAI::PlayerAI(Rules* rules) {
	r = rules;
}
/**
 * Destructor, does nothing.
 */
PlayerAI::~PlayerAI() { }

int PlayerAI::GetMove(int* moves) {
	return 0;
}
