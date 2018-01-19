#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
using namespace std;
/*
 * Abstract class, an object that chooses moves to perform.
 */
class Player {
public:
	Player();
	virtual ~Player();
	virtual int GetMove(int* moves) = 0;
	virtual int PrintActions() = 0;
	virtual void AcknowledgeMove(int x, int y) = 0;
	virtual int getColor() = 0;
};

#endif /* PLAYER_H_ */
