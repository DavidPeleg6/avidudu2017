/*
 * Player.h
 *
 *  Author: Avihai Didi
 *  ID: 313137846
 */

#ifndef PLAYER_H_
#define PLAYER_H_
using namespace std;
/**
 * Abstract class, an object that chooses moves to perform.
 */
class Player {
public:
	Player();
	virtual ~Player();
	virtual int GetMove(int* moves) = 0;
};

#endif /* PLAYER_H_ */
