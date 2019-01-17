#ifndef MINIMAX_H
#define MINIMAX_H

#include <stdio.h>
#include <limits.h>
#include <algorithm>

#include "common.h"
#include "board.h"

class Minimax{
public:
	static Pos minimax(Board *a, int d);
	static int max_value(Board *a, int alfa, int beta, int depth_max);
	static int min_value(Board *a, int alfa, int beta, int depth_max); 
};
#endif // MINIMAX_H