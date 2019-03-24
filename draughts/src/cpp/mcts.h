#ifndef MCTS_H
#define MCTS_H

#include <time.h>

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

  node(node *p, bool player, int idx){
    parent = p;
    id =  idx;

    player1 = player;
    games = 0;
    wins = 0;

    best_child = 0;
    best_value = 100;
  }

  bool has_childs(){
    return !lst_childs.empty();
  }
};

static void clean(node *n){
  for(node *x: n->lst_childs) clean(x);
  free(n);
}

static void print_tabs(int x){
  for(int i=0;i<x;i++) printf("  ");
}
static void print_tree(node *n, int tabs){
  print_tabs(tabs);
  printf("(%d,%d):\n",n->best_child,(int)n->lst_childs.size());
  for(node *a: n->lst_childs) print_tree(a,tabs+1);
}

class MCTS{
public:
  static void mcts(Board *board, int time_limit, bool player1);

  static node* select(node* root,Board *board);
  static void expand(node* n, Board *board);
  static int simulate(Board *board, bool player1, int depth_max);
  static void backpropagate(node *n, int win, bool player);

};

#endif //MCTS_H
