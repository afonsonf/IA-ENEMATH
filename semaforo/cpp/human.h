#ifndef HUMAN_H
#define HUMAN_H

#include "board.h"

class Human{
public:
  bool first_player;

  Board *board;
  bool player;

  Human(bool first_player);

  void init(Board *board);
  void play(Play p);

  void search();
  void printIndex();
  bool inRange(int x, int i, int j);
};

#endif // HUMAN_H
