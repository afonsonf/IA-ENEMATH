#include <stdio.h>

#include "board.h"
#include "minimax.h"
#include "mcts.h"

int main(){
  Board *board;

  bool player1;
  Pos p;

  int k=1,w=0,d=0,l=0,plays;
  while(k--){
    board = new Board();
    player1 = true;
    plays=0;

    // board->print_board();
    while(1){
      if(board->gameOver(player1)){
        if(player1){
          printf("B wins\n");
          l++;
        }
        else{
          printf("R wins\n");
          w++;
        }
        break;
      }
      if(plays>5){
        printf("draw\n");d++; break;
      }

      if(player1){
        //Minimax::minimax(board, 4, player1);
        MCTS::mcts(board,1000,player1);
      }

      else      {
        //Minimax::minimax(board, 4, player1);
        MCTS::mcts(board,100000,player1);
      }

      // if(player1) printf("R plays\n");
      // else        printf("B plays\n");

      p = board->best_pos;
      for(auto it = board->best_code.begin();it!=board->best_code.end(); it++){
        //printf("(%d %d) %d\n",p.i,p.j,*it);
        p=board->play(p, *it);
      }

      // board->print_board();

      player1 = !player1;
      plays++;
    }
  }

  printf("w: %d\nd: %d\nl: %d\n",w,d,l);

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
