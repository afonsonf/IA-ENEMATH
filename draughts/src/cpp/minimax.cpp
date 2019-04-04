#include "minimax.h"

#include <time.h>
#include <stdlib.h>

int Minimax::op;

//best move saved in board
void Minimax::minimax(Board *board, int depthx, bool player1, int option /*=1*/)
{
  Minimax::op = option;
  srand(time(NULL));

  board->best_pos = board->getMovablePieces(player1).front();
  board->best_code = board->getMoves(board->best_pos)[0];

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

  int nmoves=0;

  std::vector<Pos> pieces = board->getMovablePieces(true);
  std::vector<std::list<int> > moves;
  Pos px;

  int times = rand() % 20 +1;
  while(times){ std:next_permutation(pieces.begin(), pieces.end()); times--;};

  for(Pos p : pieces){ if(podar) break;
    moves = board->getMoves(p);
    for(std::list<int> codes: moves){ if(podar) break;
      px = p;

      //play
      for(auto it = codes.begin(); it!=codes.end(); it++){
        px = board->play(px,*it);
        nmoves++;
      }

      //call min
      board->depth++;
      valx = min_value(board, alfa, beta, depth_max);
      board->depth--;

      //rmplay
      while(nmoves){
        board->rmplay();
        nmoves--;
      }

      //process valx
      if (val < valx)
      {
        if (board->depth == 0){
          board->best_pos = p;
          board->best_code = codes;
        }
        val = valx;
      }

      if (val>=beta){
        podar=1;
      }

      alfa = std::max (alfa,val);
    }
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

  int nmoves=0;

  std::vector<Pos> pieces = board->getMovablePieces(false);
  std::vector<std::list<int> > moves;
  Pos px;

  int times = rand() % 20 +1;
  while(times){ std:next_permutation(pieces.begin(), pieces.end()); times--;};

  for(Pos p : pieces){ if(podar) break;
    moves = board->getMoves(p);
    for(std::list<int> codes: moves){ if(podar) break;
      px = p;

      //play
      for(auto it = codes.begin(); it!=codes.end(); it++){
        px = board->play(px,*it);
        nmoves++;
      }

      //call min
      board->depth++;
      valx = max_value(board, alfa, beta, depth_max);
      board->depth--;

      //rmplay
      while(nmoves){
        board->rmplay();
        nmoves--;
      }

      //process valx
      if (val > valx)
      {
        if (board->depth == 0){
          board->best_pos = p;
          board->best_code = codes;
        }
        val = valx;
      }

      if (val<=alfa){
        podar=1;
      }

      beta = std::min (beta,val);
    }
  }

  return val;
}
