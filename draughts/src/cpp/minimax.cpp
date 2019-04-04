#include "minimax.h"

#include <time.h>
#include <stdlib.h>

int Minimax::op;

//best move saved in board
void Minimax::minimax(Board *board, int depthx, bool player1, int option /*=1*/)
{
  Minimax::op = option;
  srand(time(NULL));

  auto plays = board->getPlays(player1);
  board->best_play = plays[0];

  //[TODO] test if wins next move

  int alfa = INT_MIN;
  int beta = INT_MAX;

  if(player1) //if we are player1, we want to maximize the board score
  max_value(board,alfa,beta,depthx);
  else //if we are not player1, we want to minimize the board score
  min_value(board,alfa,beta,depthx);
}

int Minimax::max_value(Board *board, int alfa, int beta, int depth_max)
{
  int k = board->gameEnd();
  if (k || board->depth >= depth_max)
  {
    if(k==-1) return -1000000;
    if(k==1) return 1000000;
    return board->eval_board(Minimax::op);
  }

  int val = INT_MIN, valx;
  int podar = 0;

  auto plays = board->getPlays(true);

  std::random_shuffle(plays.begin(), plays.end());

  for(Play p : plays){ if(podar) break;

    //play
    board->play(p);

    //call min
    board->depth++;
    valx = min_value(board, alfa, beta, depth_max);
    board->depth--;

    //rmplay
    board->rmplay(p);

    //process valx
    if (val < valx){
      if (board->depth == 0) board->best_play = p;
      val = valx;
    }

    if (val>=beta){
      podar=1;
    }

    alfa = std::max (alfa,val);
  }

  return val;
}

int Minimax::min_value(Board *board, int alfa, int beta, int depth_max)
{
  int k = board->gameEnd();
  if (k || board->depth >= depth_max)
  {
    if(k==-1) return -1000000;
    if(k==1) return 1000000;
    return board->eval_board(Minimax::op);
  }
  int val = INT_MAX, valx;
  int podar = 0;

  auto plays = board->getPlays(false);

  std::random_shuffle(plays.begin(),plays.end());

  for(Play p : plays){ if(podar) break;
    //play
    board->play(p);

    //call min
    board->depth++;
    valx = max_value(board, alfa, beta, depth_max);
    board->depth--;

    //rmplay
    board->rmplay(p);

    //process valx
    if (val > valx){
      if (board->depth == 0) board->best_play = p;
      val = valx;
    }

    if (val<=alfa){
      podar=1;
    }

    beta = std::min (beta,val);
  }

  return val;
}
