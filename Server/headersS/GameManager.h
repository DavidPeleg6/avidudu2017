/*
 * GameManager.h class for managing all running games
 */

#ifndef HEADERSS_GAMEMANAGER_H_
#define HEADERSS_GAMEMANAGER_H_

#include <string>
#include <vector>

using namespace std;
/*
 * a struct representing a game
 * name = game name
 * playerSocket = sockets to write to
 * status = true if game started. false otherwise
 */
struct Games {
	string name;
	int player1Socket,player2Socket;
	bool status;
};

class GameManager {

public:
	GameManager();
	vector<Games> getWaitingGames();
	int getOpponent(int player);
	vector<int> getAllPlayers();
	bool addGame(string name, int player1Socket);
	bool startGame(string name, int player2Socket);
	int* getGame(string name);
	void closeGame(string name);
	~GameManager();

private:
	vector<Games> games;
};


#endif /* HEADERSS_GAMEMANAGER_H_ */
