#ifndef PLAY_H
#define PLAY_H

#include <stdio.h>
#include <list>

//define Play
struct Play{
  int i;
  int j;

  //define operator==
  inline bool operator==(const Play& p1){
    return this->i == p1.i && this->j == p1.j;
  }
};

//print play in one line
static void printPlay(Play p){
  printf("(%d %d)",p.i,p.j);
  printf("\n"); //end it with nl
}

#endif // PLAY_H
