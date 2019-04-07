#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>

struct Pos{
  int i;
  int j;

  inline int operator< (Pos b){
    if(i==b.i) return j<b.j;
    return i<b.i;
  }

  inline bool operator==(const Pos& p1){
      return p1.i == this->i && p1.j == this->j;
  }
};

static Pos mk_Pos(int i, int j){
  Pos p;
  p.i = i, p.j = j;
  return p;
}

struct Move{
  Pos last_pos;
  int last_code;
  int last_eat;
  bool last_up;
};

struct Play{
  Pos piece;
  std::list<int> codes;

  inline bool operator==(const Play& p1){
    if(!(this->piece == p1.piece)) return false;
    if(p1.codes.size() != this->codes.size()) return false;

    auto it1 = p1.codes.begin();
    auto it2 = this->codes.begin();
    for(;it1!=p1.codes.end() && it2!=this->codes.end();it1++,it2++){
      if(*it1 != *it2) return false;
    }

    return true;
  }
};

static int sign(int val) {
  if (val > 0) return 1;
  if (val < 0) return -1;
  return 0;
}

static void print_moves(std::vector<std::list<int> > moves){
  printf("size: %d\n",(int)moves.size());
  for(int i=0;i<(int)moves.size();i++){
    for(int code : moves[i]) printf("%d ",code);
  }
}

#define valueOfKing 5

#endif //COMMON_H
