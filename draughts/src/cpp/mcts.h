#ifndef MCTS_H
#define MCTS_H

#include "common.h"
#include "board.h"

struct node{
  node* parent;

  bool player1;
  int games;
  int wins;
  int id;

  std::vector<Pos> lst_pos;
  std::vector<std::list<int> > lst_moves;
  std::vector<node*> lst_childs;

  int best_child;
  double best_value;

  node(node *p, bool player, int id){
    parent = p;

    player1 = player;
    games = 0;
    wins = 0;

    best_child = 0;
    best_value = 0;
  }

  bool has_childs(){
    return lst_childs.empty();
  }
};

static void clean(node *n){
  for(node *x: n->lst_childs) clean(x);
  free(n);
}

class MCTS{
public:
  static void mcts(Board *board, bool player1, int time_limit);

  static node* select(node* root,Board *board);
  static void expand(node* n, Board *board);
  static int simulate(Board *board, bool player1, int depth_max);
  static void backpropagate(node *n, int win);

};

#endif //MCTS_H
