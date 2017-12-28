#ifndef CONSOLEDISPLAY_H_
#define CONSOLEDISPLAY_H_
#include <iostream>
#include "Board.h"
#include "Display.h"
using namespace std;
/*
 * A type of display that outputs the game onto a text screen.
 */
class ConsoleDisplay : public Display {
public:
	ConsoleDisplay();
	virtual ~ConsoleDisplay();
	void Print(Board* b, int turn, int* moves);
	void PrintBoard(Board* b);
	void AskForMove();
	void InvalidMove();
	void InvalidFormat();
	void DeclareWinner(int* state);
	void StatePlay(int x, int y, int player);
	void AskForPlayer(int playerNum);
	void InvalidChoice();
	void WaitForOtherPlayer();
	void PrintGameList(char** games);
	void ServerCrash();
private:
	void PrintDashLine(Board* b);
	void PrintTurn(int turn);
	void PrintMoves(int* moves);
};

#endif /* CONSOLEDISPLAY_H_ */
