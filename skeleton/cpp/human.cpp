#include "human.h"

Human::Human(bool first_player){
  this->first_player = first_player;
}

void Human::init(Board *board){
  this->board = board;
  player = first_player;
}

void Human::play(Play p){
  player = !player;
}

void Human::search(){
  int index = -1;

  auto lst_plays = board->getPlays(player);
  int sz = lst_plays.size();

  board->print_board();

  for(int i=0;i<sz;i++){
    printf("%d: ",i);
    printPlay(lst_plays[i]);
  }printf("\n");

  while(1){
      printf("Choose a move: "); fflush(stdout);
      scanf("%d",&index);

      if(!inRange(index,0,sz-1)) printf("Invalid move\n");
      else break;
  }

  board->best_play = lst_plays[index];
}

bool Human::inRange(int x, int i, int j){
  return x>=i && x<=j;
}
