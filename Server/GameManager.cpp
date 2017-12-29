#include "headersS/GameManager.h"

GameManager::GameManager() {
}
/*
 * returns all games that haven't started
 */
vector<Games> GameManager::getWaitingGames() {
	vector<Games> deadGames;
	vector<Games>::iterator it;
	for(it = games.begin(); it != games.end(); ++it) {
		//if game hasnt started
		if(!(it -> status)) {
			//deep copy
			Games temp;
			temp.name = it -> name;
			temp.player1Socket = it -> player1Socket;
			temp.status = false;
			deadGames.push_back(temp);
		}
	}
	return deadGames;
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
	Games newGame;
	newGame.name = name;
	newGame.player1Socket = player1Socket;
	newGame.player2Socket = 0;
	newGame.status = false;
	games.push_back(newGame);
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
		games.erase(it);
	}
}

/*
 * return all waiting and running player sockets
 */
vector<int> GameManager::getAllPlayers() {
	vector<int> players;
	vector<Games>::iterator it;
	for(it = games.begin(); it != games.end(); ++it) {
		players.push_back(it->player1Socket);
		if(it->status) {
			players.push_back(it->player2Socket);
		}
	}
	return players;
}

int* GameManager::getGame(string name) {
	int* players = new int[2];
	vector<Games>::iterator it;
	for(it = games.begin(); it != games.end(); ++it) {
		if(!(it->name).compare(name)) {
			players[0] = it->player1Socket;
			players[1] = it->player2Socket;
			return players;
		}
	}
	return NULL;
}

int GameManager::getOpponent(int player) {
	vector<Games>::iterator it;
	for(it = games.begin(); it != games.end(); ++it) {
		if(player == it->player1Socket) {
			return it->player2Socket;
		} else if (player == it->player2Socket) {
			return it->player1Socket;
		}
	}
	return 0;
}
