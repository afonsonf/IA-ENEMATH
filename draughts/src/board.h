#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <string.h>
#include <utility>

#include "common.h"

class Board{
public:
	int board[8][8];

	Pos last_play;
  int last_code;
  bool last_up;

	Pos best_play;
	int depth;

	Board();

	bool play(Pos p, int code);
	bool rmplay(Pos last_p, int last_c);

  bool inBounds(Pos p);
  bool open(Pos p);
  bool jumpOK(Pos p1, Pos p2);

  bool canJump(Pos p);
  bool canStep(Pos p);

  bool final_board();
	int eval_board();

	void print_board();
};

#endif // BOARD_H
