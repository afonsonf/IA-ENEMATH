#include <stdio.h>

#include "board.h"
#include "minimax.h"
#include "mcts.h"

#define SEE false

int main(){
  Board *board;

  MCTS *p1 = new MCTS();
  //MCTS *p2 = new MCTS();
  Minimax *p2 = new Minimax();
  bool player1;
  Pos p;

  int k=200,w=0,d=0,l=0,plays;
  while(k--){
    board = new Board();

    player1 = false;

    //p1 is true
    //p2 is false

    p1->init(board,100000, player1);
    p2->init(board,4,false,1);
    //p2->init(board,10000, player1);

    plays=0;

    if(SEE) board->print_board();
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

      if(player1)p1->search();
      else p2->search();

      if(SEE){
        if(player1) printf("R plays\n");
        else        printf("B plays\n");
      }

      board->play(board->best_play);
      p1->play(board->best_play);
      p2->play(board->best_play);

      if(SEE)board->print_board();

      player1 = !player1;
      plays++;
    }
  }

  printf("w: %d\nd: %d\nl: %d\n",w,d,l);

  return 0;
}
