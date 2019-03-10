#ifndef MINIMAX_H
#define MINIMAX_H

#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <stack>

#include "common.h"
#include "board.h"

class Minimax{
public:
	static Pos minimax(Board *board, int d, bool player);
	static int max_value(Board *board, int alfa, int beta, int depth_max);
	static int min_value(Board *board, int alfa, int beta, int depth_max);
};
#endif // MINIMAX_H
