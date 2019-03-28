#ifndef MCTS_H
#define MCTS_H

#include <time.h>
#include <math.h>
#include "common.h"
#include "board.h"

const double EXPLOR_PARAM = 1.3;

struct node{
  node* parent;

  bool player1;
  int games;
  int wins;
  int id;

  std::vector<Pos> lst_pos;
  std::vector<std::list<int> > lst_moves;
  std::vector<node*> lst_childs;

  node(node *p, bool player, int idx){
    parent = p;
    id =  idx;

    player1 = player;
    games = 0;
    wins = 0;
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


class MCTS{
public:
  static void mcts(Board *board, int time_limit, bool player1);

  static double eval(node *n, int tot,bool p);
  static int select_child(node* n,bool p);
  static node* select(node* root,Board *board);
  static void expand(node* n, Board *board);
  static int simulate(Board *board, bool player1, int depth_max);
  static void backpropagate(node *n, int win,bool player);

};

static void print_tree(node *n, int tabs){
  return;
  
  if(!n->has_childs()) return;
  print_tabs(tabs);
  //if(n->parent) printf("(%.3lf,%d):\n",MCTS::eval(n,n->parent->games),(int)n->games);
  //else printf("(--,%d):\n",(int)n->games);
  for(node *a: n->lst_childs) print_tree(a,tabs+1);
}

#endif //MCTS_H
