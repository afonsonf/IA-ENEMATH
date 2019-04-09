#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <stack>

#include "play.h"

class Board{
public:
	std::stack<Play> playsStack;

	Play best_play;
	int depth;

	Board();
	Board* dup();

	void play(Play p);
	void rmplay();

	std::vector<Play> getPlays(bool player);

	int whoWins(bool next_player);
	bool isDraw();
	bool gameOver(bool next_player);

	int eval_board();

	void print_board();
};

#endif // BOARD_H
