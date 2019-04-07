#ifndef MINIMAX_H
#define MINIMAX_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <stack>

#include "common.h"
#include "board.h"

class Minimax{
public:
	Board *board;
	int depth;
	bool player;
	int option;

	Minimax();

	void init(Board *board, int depth, bool player, int option = 1);
	void play(Play p){}

	void search();
	int max_value(Board *board, int alfa, int beta, int depth_max);
	int min_value(Board *board, int alfa, int beta, int depth_max);
};
#endif // MINIMAX_H
