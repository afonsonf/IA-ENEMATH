#include <stdio.h>

#include "board.h"
#include "minimax.h"
#include "mcts.h"
#include "human.h"

#define SEE true

int main(){
  Board *board;
  bool first_player = true;

  /*-----------------------------------------------------------*/

  MCTS *p1 = new MCTS(2500000, first_player);
  // MCTS *p2 = new MCTS(10000, first_player);

  // Minimax *p1 = new Minimax(6,first_player);
  Minimax *p2 = new Minimax(2,first_player);

  // Human *p1 = new Human(first_player);
  //Human *p2 = new Human(first_player);

  /*-----------------------------------------------------------*/

  bool player;

  int k=1,w=0,d=0,l=0,plays,win;
  while(k--){
    //if(board) delete(board);
    board = new Board();

    player = first_player;

    p1->init(board);
    p2->init(board);

    plays=0;
    if(SEE) board->print_board();
    while(1){
      if(board->gameOver(player)){
        win = board->whoWins(player);
        if(win == -1){
          l++;
          printf("B wins (%2d::%2d::%2d)\n",w,d,l);
        }
        else if(win == 1){
          w++;
          printf("R wins (%2d::%2d::%2d)\n",w,d,l);
        }
        else{
          d++;
          printf("draw   (%2d::%2d::%2d)\n",w,d,l);
        }
        break;
      }

      if(plays>120){
        d++;
        printf("draw   (%2d::%2d::%2d)\n",w,d,l);
        break;
      }

      if(player) p1->search();
      else p2->search();

      if(SEE){
        if(player) printf("R plays\n");
        else       printf("B plays\n");
      }

      board->play(board->best_play);
      p1->play(board->best_play);
      p2->play(board->best_play);

      if(SEE)board->print_board();

      player = !player;
      plays++;
    }
    delete(board);
  }

  printf("w: %d\nd: %d\nl: %d\n",w,d,l);

  return 0;
}
