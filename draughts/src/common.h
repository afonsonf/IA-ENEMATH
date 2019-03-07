#ifndef COMMON_H
#define COMMON_H

typedef struct {
  int i;
  int j;
} Pos;

Pos mk_Pos(int i, int j){
  Pos p;
  p.i = i, p.j = j;
  return p;
}

int sign(int val) {
  if (val > 0) return 1;
  if (val < 0) return -1;
  return 0;
}

#endif //COMMON_H
