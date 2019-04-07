#include <stdio.h>

#include "board.h"
#include "minimax.h"
#include "mcts.h"

#define SEE false

int main(){
  Board *board;

  bool player1;
  Pos p;

  int k=200,w=0,d=0,l=0,plays;
  while(k--){
    board = new Board();
    player1 = false;
    plays=0;

    if(SEE)board->print_board();
    while(1){
      if(board->gameOver(player1)){
        if(player1){
          l++;
          printf("B wins (%2d::%2d::%2d)\n",w,d,l);
        }
        else{
          w++;
          printf("R wins (%2d::%2d::%2d)\n",w,d,l);
        }
        break;
      }
      if(plays>120){
        d++;
        printf("draw   (%2d::%2d::%2d)\n",w,d,l);
        break;
      }

      if(player1){
        Minimax::minimax(board, 4, player1, 1);
        //MCTS::mcts(board,10000,player1);
        //return 0;
      }

      else      {
        //Minimax::minimax(board, 2, player1, 1);
        MCTS::mcts(board,250000,player1);
        //return 0;
      }

      if(SEE){
        if(player1) printf("R plays\n");
        else        printf("B plays\n");
      }

      board->play(board->best_play);

      if(SEE)board->print_board();

      player1 = !player1;
      plays++;
    }
  }

  printf("w: %d\nd: %d\nl: %d\n",w,d,l);

  return 0;
}
