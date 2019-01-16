#ifndef MINIMAX_H
#define MINIMAX_H

#include <stdio.h>
#include <limits.h>

#include "common.h"
#include "board.h"

class Minimax{
public:
	static Pos minimax(Board *a, int d);
	static int max_value(Board *a,int depth_max);
	static int min_value(Board *a,int depth_max); 
};
#endif // MINIMAX_H