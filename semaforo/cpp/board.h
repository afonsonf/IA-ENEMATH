#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <stack>

#include "play.h"
#include "eval.h"

class Board{
public:
	std::stack<Play> playsStack;

	Play best_play;
	int depth;

	int board[3][4];

	Board();
	void init();
	Board* dup();

	void play(Play p);
	void rmplay();

	std::vector<Play> getPlays(bool player);

	bool final_board();

	int whoWins(bool next_player);
	bool isDraw();
	bool gameOver(bool next_player);

	int eval_board();

	void print_board();
};

#endif // BOARD_H
