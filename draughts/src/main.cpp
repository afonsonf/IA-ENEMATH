#include <stdio.h>

#include "board.h"
#include "minimax.h"

int main(){
  Board *board = new Board();

  bool player1 = true;
  Pos p;

  board->print_board();
  while(1){
    if(board->gameOver(player1)){
      if(player1) printf("B wins\n");
      else printf("A wins\n");
      break;
    }
    if(player1)
      Minimax::minimax(board, 3, player1);
    else
      Minimax::minimax(board, 9, player1);
    p = board->best_play;
    for(auto it = board->best_code.begin();it!=board->best_code.end(); it++)
      p=board->play(p, *it);

    board->print_board();

    player1 = !player1;
  }


  return 0;
}

/*
board->print_board();

board->play(mk_Pos(1,5), 4);
board->play(mk_Pos(0,4), 5);

board->play(mk_Pos(5,5), 4);
board->play(mk_Pos(4,4), 4);

board->play(mk_Pos(6,6), 4);

board->print_board();

std::vector<std::list<int> > moves;
moves = board->getMoves(mk_Pos(2,2));
print_moves(moves);
*/
