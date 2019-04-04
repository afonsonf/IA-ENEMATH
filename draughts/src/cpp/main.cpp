#include <stdio.h>

#include "board.h"
#include "minimax.h"
#include "mcts.h"

#define SEE false

int main(){
  Board *board;

  bool player1;
  Pos p;

  int k=50,w=0,d=0,l=0,plays;
  while(k--){
    board = new Board();
    player1 = false;
    plays=0;

    if(SEE)board->print_board();
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
      if(plays>120){
        printf("draw\n");d++; break;
      }

      if(player1){
        //Minimax::minimax(board, 4, player1, 1);
        MCTS::mcts(board,500000,player1);
        //return 0;
      }

      else      {
        Minimax::minimax(board, 6, player1, 1);
        //MCTS::mcts(board,50000,player1);
        //return 0;
      }

      if(SEE){
        if(player1) printf("R plays\n");
        else        printf("B plays\n");
      }

      p = board->best_pos;
      for(auto it = board->best_code.begin();it!=board->best_code.end(); it++){
        //printf("(%d %d) %d\n",p.i,p.j,*it);
        p=board->play(p, *it);
      }

      if(SEE)board->print_board();

      player1 = !player1;
      plays++;
    }
  }

  printf("w: %d\nd: %d\nl: %d\n",w,d,l);

  return 0;
}
