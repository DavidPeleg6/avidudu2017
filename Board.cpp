/*
 * Board.cpp
 *
 *  Author: Avihai Didi
 *  ID: 313137846
 */
#include "Board.h"
#include <iostream>
using namespace std;
/**
 * Constructor: Makes the board and fills it with blanks.
 */
Board::Board() {
	width = 8;
	height = 8;
	b = new int*[height];
	for (int i = 0; i < height; i++) {
		b[i] = new int[width];
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			b[i][j] = 0;
		}
	}
}
/**
 * Constructor: Makes the board and fills it with blanks.
 */
Board::Board(int board_width, int board_height) {
	width = board_width;
	height = board_height;
	b = new int*[height];
	for (int i = 0; i < height; i++) {
		b[i] = new int[width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			b[i][j] = 0;
		}
	}
}

/**
 * Destructor: Deletes the board and all its contents.
 */
Board::~Board() {
	for (int i = 0;i < height; i++) {
		delete[] b[i];
	}
	delete b;
}
/*
 * This function returns the value of the board at location (x,y).
 * @param x: x cord. from 1 to width
 * @param y: y cord. from 1 to height
 */
int Board::get(int x, int y) {
	if (x <= 0 || width < x || y <= 0 || height < y) {
		return 0;
	}
	return b[y - 1][x - 1];
}
/*
 * Returns the width of the board.
 * @return - width of the board.
 */
int Board::getWidth() {
	return width;
}
/*
 * Returns the height of the board.
 * @return - height of the board.
 */
int Board::getHeight() {
	return height;
}
/*
 * This function sets the value of the board at location (x,y).
 * @param x - x cord. from 1 to width
 * @param y - y cord. from 1 to height
 * @param value - the value to be set.
 */
void Board::set(int x, int y, int value) {
	if (!(x <= 0 || width < x || y <= 0 || height < y)) {
		b[y - 1][x - 1] = value;
	}
}
/**
 * This function places the initial 4 pieces on a 8x8 game.
 */
void Board::SetUpGame() {
	set(4, 4, 1);
	set(5, 5, 1);
	set(4, 5, 2);
	set(5, 4, 2);
}

Board* Board::simBoard() {
	Board *copiedBoard = new Board(this->width, this->height);
	for(int rows = 1; rows <= this->height; rows++) {
		for(int cols = 1; cols <= this->width; cols++) {
			copiedBoard->set(rows, cols, b[rows][cols]);
		}
	}
	return copiedBoard;
}

