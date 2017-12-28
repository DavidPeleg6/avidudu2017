#include "headersS/GameManager.h"

GameManager::GameManager() {
}
/*
 * returns all games
 */
vector<Games> GameManager::getGames() {
	return games;
}
/*
 * adds the second player to the waiting game
 * name = game name
 * player2Socket = socket of the new player
 * return = false if game is full
 */
bool GameManager::startGame(string name, int player2Socket) {
	vector<Games>::iterator it;
	for(it = games.begin(); it != games.end(); ++it) {
		if(!name.compare(it -> name)) {
			//check if game is full
			if(it -> status) {
				break;
			}
			it -> player2Socket = player2Socket;
			it -> status = true;
			return true;
		}
	}
	return false;
}

/*
 * adds a new waiting game to the list
 * name = game name
 * player1Socket = socket of the new player
 * return = false if name is taken
 */
bool GameManager::addGame(string name, int player1Socket) {
	vector<Games>::iterator it;
	for(it = games.begin(); it != games.end(); ++it) {
		if(!name.compare(it -> name)) {
			return false;
		}
	}
	Games* newGame = new Games;
	newGame -> name = name;
	newGame -> player1Socket = player1Socket;
	newGame -> status = false;
	games.push_back(*newGame);
	return true;
}

/*
 * closes an existing game
 * name = game name
 */
void GameManager::closeGame(string name) {
	vector<Games>::iterator it;
	for(it = games.begin(); it != games.end(); ++it) {
		if(!name.compare(it -> name)) {
			delete &it;
			games.erase(it);
		}
	}
}
/*
 * destructor method for safe delete
 */
GameManager::~GameManager() {
	vector<Games>::iterator it;
	for(it = games.begin(); it != games.end(); ++it) {
		delete &it;
		games.erase(it);
	}
}
