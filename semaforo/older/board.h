#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <string.h>
#include <utility>

#include "eval.h"
#include "common.h"

class Board{
public:
	int board[3][4];
	Pos last_play;
	Pos best_play;
	int depth;

	Board();

	bool play(Pos p);
	bool rmplay(Pos p);

  bool final_board();
	int eval_board();

	void print_board();
};

#endif // BOARD_H
