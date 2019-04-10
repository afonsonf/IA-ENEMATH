#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <stack>

#include "play.h"
#include "common.h"
#include "myboost.h"

class Board{
public:
	std::stack<Play> playsStack;

	Play best_play;
	int depth;

	int board[6][7];
	int np[7];

	Board();
	Board* dup();

	void play(Play p);
	void rmplay();

	int pos(int i,int j);

	std::vector<Play> getPlays(bool player);

	int final_board();

	Play winPlay(bool next_player);
	Play savePlay(bool next_player);

	int whoWins(bool next_player);
	bool isDraw();
	bool gameOver(bool next_player);

	int eval_board();

	void print_board();
};

#endif // BOARD_H
