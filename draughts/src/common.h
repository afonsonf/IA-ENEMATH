#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <vector>
#include <list>

struct Pos{
  int i;
  int j;
};

static Pos mk_Pos(int i, int j){
  Pos p;
  p.i = i, p.j = j;
  return p;
}

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
