#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <string.h>
#include <utility>
#include <vector>
#include <list>
#include <stack>

#include "common.h"

class Board{
public:
	int board[8][8];
	int numberPieces;

	std::stack<Move> movesStack;

	Play best_play;

	int depth;

	Board();
	Board* dup();

	bool validMove(Pos p, int code);

	Pos play_aux(Pos p, int code);
	void rmplay_aux();

	void play(Play p);
	void rmplay(Play p);

  bool inBounds(Pos p);
  bool open(Pos p);
  bool jumpOK(Pos p1, Pos p2);

  bool canJump(Pos p);
  bool canStep(Pos p);

	std::vector<Pos> getMovablePieces (bool player1);
	bool gameOver(bool player1);
	int gameEnd();

	std::vector<std::list<int> > getJumpMoves(Pos p);
	std::vector<std::list<int> > getStepMoves(Pos p);
	std::vector<std::list<int> > getMoves(Pos p);

	std::vector<Play> getPlays(bool player1);

	int eval_board(int op = 1);
	int eval_board_1();
	int eval_board_2();

	void print_board();
};

#endif // BOARD_H
