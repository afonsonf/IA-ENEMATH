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

  printIndex();

  for(int i=1;i<=sz;i++){
    printf("%d: ",i);
    printPlay(lst_plays[i-1]);
    printf("\n");
  }printf("\n");

  while(1){
      printf("Choose a move: "); fflush(stdout);
      scanf("%d",&index);

      if(!inRange(index,1,sz)) printf("Invalid move\n");
      else break;
  }

  board->best_play = lst_plays[index-1];
}

void Human::printIndex(){
  printf("Code 0 - step right up\n");
  printf("Code 1 - step right down\n");
  printf("Code 2 - jump right up\n");
  printf("Code 3 - jump right down\n");
  printf("Code 4 - step left up\n");
  printf("Code 5 - step left down\n");
  printf("Code 6 - jump left up\n");
  printf("Code 7 - jump left down\n");
  printf("\n");
}

bool Human::inRange(int x, int i, int j){
  return x>=i && x<=j;
}
