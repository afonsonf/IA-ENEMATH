#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <string.h>
#include <utility>
#include <vector>
#include <list>

#include "common.h"

class Board{
public:
	int board[8][8];

	Pos last_play;
  int last_code;
  bool last_up;

	Pos best_play;
	std::list<int> best_code;

	int depth;

	Board();

	Pos play(Pos p, int code);
	Pos rmplay(Pos last_p, int last_c,bool last_u);

  bool inBounds(Pos p);
  bool open(Pos p);
  bool jumpOK(Pos p1, Pos p2);

  bool canJump(Pos p);
  bool canStep(Pos p);

	std::vector<Pos> getMovablePieces (bool player1);
	int gameEnd();

	std::vector<std::list<int> > getJumpMoves(Pos p);
	std::vector<std::list<int> > getStepMoves(Pos p);
	std::vector<std::list<int> > getMoves(Pos p);
  //bool final_board();
	//int eval_board();

	void print_board();
};

#endif // BOARD_H
