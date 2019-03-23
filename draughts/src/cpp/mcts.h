#ifndef MCTS_H
#define MCTS_H

#include "common.h"
#include "board.h"

struct node{
  //node* parent;
  int games;
  int wins;
  std::vector<std::list<int> > lst_moves;
  std::vector<node*> lst_childs;

  //best_child
  //best_value

  node(){
    games = 0;
    wins = 0;
  }

  void expand(Board *board, bool player1){
     //expand childs
  }

  bool has_childs(){
    return lst_childs.empty();
  }
};

static void clean(node *n){
  //clean
}

class MCTS{
public:
  int start_time;

  //node* select();
  //int simulate(node *n);
  //void backpropagate(node *n);

};

#endif //MCTS_H
