#ifndef PLAY_H
#define PLAY_H

#include <stdio.h>
#include <list>

//define Play
struct Play{
  int col;
  int player;

  //define operator==
  inline bool operator==(const Play& p1){
    return this->col == p1.col && this->player == p1.player;
  }
};

//print play in one line
static void printPlay(Play p){
  printf(" %d",p.col);
  printf("\n"); //end it with nl
}

#endif // PLAY_H
