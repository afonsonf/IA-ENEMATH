#ifndef MINIMAX_H
#define MINIMAX_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include "play.h"
#include "board.h"

class Minimax{
public:
	int depth;
	bool first_player;

	Board *board;
	bool player;

	Minimax(int depth, bool first_player);

	void init(Board *board);
	void play(Play p);

	void search();
	int max_value(Board *board, int alfa, int beta, int depth_max);
	int min_value(Board *board, int alfa, int beta, int depth_max);
};
#endif // MINIMAX_H
