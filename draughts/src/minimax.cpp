#include "minimax.h"

#include <time.h>
#include <stdlib.h>

long long expandidos2; //number of nodes expanded
long long int podas;//number of prunes

Pos Minimax::minimax(Board *board, int depthx, bool player1)
{
  board->best_play = board->getMovablePieces(player1).front();
  board->best_code = board->getMoves(board->best_play)[0];

  //[TODO] test if wins next move

  expandidos2 = 0;
  podas = 0;

  int alfa = INT_MIN;
  int beta = INT_MAX;

  if(player1) //if we are player1, we want to maximize the board score
    max_value(board,alfa,beta,depthx);
  else //if we are not player1, we want to minimize the board score
    min_value(board,alfa,beta,depthx);

  //printf("Numero de podas: %lld\n",podas);
  //printf("Nos expandidos: %lld\n", expandidos2);
  return board->best_play;
}

int Minimax::max_value(Board *board, int alfa, int beta, int depth_max)
{

  int k = board->gameEnd();
  if (k || board->depth >= depth_max)
  {
    if(k==-1) return -1000000;
    if(k==1) return 1000000;
    return 0;
    //return board->eval();
  }

  int val = INT_MIN, valx;
  int podar = 0;

  std::stack<Pos> lplay;
  std::stack<int> lcode;
  std::stack<bool> lup;

  std::vector<Pos> pieces = board->getMovablePieces(true);
  std::vector<std::list<int> > moves;
  Pos px;

  for(Pos p : pieces){ if(podar) break;
    moves = board->getMoves(p);
    px = p;
    for(std::list<int> codes: moves){ if(podar) break;
      //play
      for(auto it = codes.begin(); it!=codes.end(); it++){
        lplay.push(board->last_play); lcode.push(board->last_code); lup.push(board->last_up);
        px = board->play(px,*it);
      }

      //call min
      board->depth++;
      valx = min_value(board, alfa, beta, depth_max);
      board->depth--;

      //rmplay
      while(!lplay.empty()){
        board->rmplay(lplay.top(), lcode.top(), lup.top());
        lplay.pop(); lcode.pop(); lup.pop();
      }

      //process valx
      if (val < valx)
      {
        if (board->depth == 1){
          board->best_play = p;
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
    return 0;
    //return board->eval();
  }
  int val = INT_MAX, valx;
  int podar = 0;

  std::stack<Pos> lplay;
  std::stack<int> lcode;
  std::stack<bool> lup;

  std::vector<Pos> pieces = board->getMovablePieces(true);
  std::vector<std::list<int> > moves;
  Pos px;

  for(Pos p : pieces){ if(podar) break;

    moves = board->getMoves(p);
    px = p;
    for(std::list<int> codes: moves){ if(podar) break;

      //play
      for(auto it = codes.begin(); it!=codes.end(); it++){
        lplay.push(board->last_play); lcode.push(board->last_code); lup.push(board->last_up);
        px = board->play(px,*it);
      }

      //call min
      board->depth++;
      valx = max_value(board, alfa, beta, depth_max);
      board->depth--;

      //rmplay
      while(!lplay.empty()){
        board->rmplay(lplay.top(), lcode.top(), lup.top());
        lplay.pop(); lcode.pop(); lup.pop();
      }

      //process valx
      if (val > valx)
      {
        if (board->depth == 1){
          board->best_play = p;
          board->best_code = codes;
        }
        val = valx;
      }

      if (val<=alfa){
        podar=1;
      }

      beta = std::min (alfa,val);
    }
  }

  return val;
}
