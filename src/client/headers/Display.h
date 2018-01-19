#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <iostream>
#include "Board.h"
using namespace std;
/**
 * Abstract, the object that will visually displays the game to the user.
 */
class Display {
public:
	Display();
	virtual ~Display();
	virtual void Print(Board* b, int turn, int* moves) = 0;
	virtual void PrintBoard(Board* b) = 0;
	virtual void AskForMove() = 0;
	virtual void InvalidMove() = 0;
	virtual void InvalidFormat() = 0;
	virtual void DeclareWinner(int* state) = 0;
	virtual void StatePlay(int x, int y, int player) = 0;
	virtual int AskForPlayer(int playerNum) = 0;
	virtual void InvalidChoice() = 0;
	virtual void WaitForOtherPlayer() = 0;
	virtual void PrintGameList(char** games) = 0;
	virtual void GameAlreadyExists() = 0;
	virtual void GameDoesntExist() = 0;
	virtual void ServerCrash() = 0;
	virtual void ServerCrash(const char* msg) = 0;
	virtual void WaitForOpponent() = 0;
	virtual char* GetClientCommand() = 0;
	virtual int GetMove(int* moves) = 0;
private:
	virtual void PrintDashLine(Board* b) = 0;
	virtual void PrintTurn(int turn) = 0;
	virtual void PrintMoves(int* moves) = 0;
};

#endif /* DISPLAY_H_ */
