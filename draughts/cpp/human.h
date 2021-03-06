#ifndef HUMAN_H
#define HUMAN_H

#include <stdio.h>
#include <string.h>

#include "board.h"
#include "common.h"

class Human{
public:
  bool first_player;

  Board *board;
  bool player;

  Human(bool first_player);

  void init(Board *board);
  void play(Play p);

  int getInput(int sz);
  void search();
  void printIndex();
  bool inRange(int x, int i, int j);
};

#endif // HUMAN_H
