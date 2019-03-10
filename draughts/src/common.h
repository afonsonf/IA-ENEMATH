#ifndef COMMON_H
#define COMMON_H

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

#endif //COMMON_H
