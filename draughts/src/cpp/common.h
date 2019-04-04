#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>

struct Pos{
  int i;
  int j;

  int operator< (Pos b){
    if(i==b.i) return j<b.j;
    return i<b.i;
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
};

static int sign(int val) {
  if (val > 0) return 1;
  if (val < 0) return -1;
  return 0;
}

static void print_moves(std::vector<std::list<int> > moves){
  printf("size: %d\n",(int)moves.size());
  for(int i=0;i<(int)moves.size();i++){
    printf("a ");
    for(int code : moves[i]) printf("%d ",code);
    printf("b\n");
  }
}

#define valueOfKing 5

#endif //COMMON_H
