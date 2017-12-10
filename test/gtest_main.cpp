/*
 * gtest_main.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: david
 */

#include "gtest/gtest.h"
#include <iostream>
#include "headers/Board.h"
#include "headers/Game.h"
#include "headers/Rules.h"
#include "headers/Player.h"
#include "headers/PlayerAI.h"

GTEST_API_ int main(int argc,char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

struct BoardFix: testing::Test {
	Board *board;
	BoardFix() {
		board = new Board();
		board->SetUpGame();
	}
	~BoardFix() {
		delete board;
	}
};

TEST_F(BoardFix, board_is_good) {
	cout << "testing board class" << endl;
	board->set(6,5,1);
	EXPECT_EQ(0, board->get(0,0));
	EXPECT_EQ(2, board->get(4,5));
	EXPECT_EQ(1, board->get(6,5));
	Board *board2 = board->SimBoard();
	EXPECT_EQ(0, board2->get(0,0));
	EXPECT_EQ(1, board2->get(6,5));
	delete board2;
}

struct RulesTest: testing::Test {
	Board *board;
	Rules *rules;
	RulesTest() {
		board = new Board();
		board->SetUpGame();
		rules = new Rules(board);
	}
	~RulesTest() {
		delete rules;
		delete board;
	}

};
TEST_F(RulesTest, rules_work) {
	EXPECT_EQ(0, rules->CheckBoardState()[0]);
	EXPECT_EQ(2, rules->Score(1));
	EXPECT_EQ(2, rules->Score(2));
	int *moves = rules->PossibleMoves(1);
	EXPECT_EQ(8, moves[0]);
	EXPECT_EQ(3, moves[1]);
	EXPECT_EQ(5, moves[2]);
	rules->SetPiece(1, 3, 5);
	EXPECT_EQ(0, rules->CheckBoardState()[0]);
	EXPECT_EQ(4, rules->Score(1));
	EXPECT_EQ(1, rules->Score(2));
	moves = rules->PossibleMoves(1);
	EXPECT_EQ(6, moves[0]);
	EXPECT_EQ(5, moves[1]);
	EXPECT_EQ(3, moves[2]);
}

struct PlayerAITest: testing::Test {
	Board *board;
	Rules *rules;
	PlayerAI *player1, *player2;
	PlayerAITest() {
		board = new Board();
		board->SetUpGame();
		rules = new Rules(board);
		player1 = new PlayerAI(rules, board, 1);
		player2 = new PlayerAI(rules, board, 2);
	}
	~PlayerAITest() {
		delete rules;
		delete board;
		delete player1;
		delete player2;
	}

};
TEST_F(PlayerAITest, AIsmart) {
	int *moves = rules->PossibleMoves(1);
	EXPECT_EQ(1, player1->GetMove(moves));
	rules->SetPiece(1, moves[1], moves[2]);
	moves = rules->PossibleMoves(2);
	EXPECT_EQ(1, player2->GetMove(moves));

}

TEST(FileReaderTest, Reader_Works) {
	FileReader reader("ipfile");
	int* data = reader->read();
	EXPECT_EQ(127, data[0]);
	EXPECT_EQ(0, data[1]);
	EXPECT_EQ(0, data[0]);
	EXPECT_EQ(1, data[2]);
	EXPECT_EQ(51111, data[3]);
}
