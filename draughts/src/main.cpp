#include <stdio.h>

#include "board.h"
#include "minimax.h"

int main(){
  Board *b = new Board();
  b->print_board();

  Minimax::minimax(b, 1, true);

  return 0;
}

/*
b->play(mk_Pos(0,2), 1);
b->play(mk_Pos(1,3), 0);
b->play(mk_Pos(0,4), 1);
b->play(mk_Pos(1,5), 0);
b->play(mk_Pos(0,6), 1);
b->rmplay(mk_Pos(0,6),0,false);
b->rmplay(mk_Pos(1,5),1,false);
b->rmplay(mk_Pos(0,4),0,false);
b->rmplay(mk_Pos(1,3),1,false);
b->rmplay(mk_Pos(0,2),-1,false);
*/
