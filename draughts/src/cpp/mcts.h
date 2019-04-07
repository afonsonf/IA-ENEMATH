#ifndef MCTS_H
#define MCTS_H

#include <time.h>
#include <math.h>
#include "common.h"
#include "board.h"

struct Node{
  Node* parent;

  bool next_player;
  int games;
  int wins;

  Board *board;

  std::vector<Play> lst_plays;
  std::vector<Node*> lst_childs;

  Node(Node *node, bool player, Board *board){
    this->parent = node;
    this->board = board;

    this->next_player = player;
    this->games = 0;
    this->wins = 0;
  }

  bool has_childs(){
    return !lst_childs.empty();
  }
};

static void clean(Node *n){
  for(Node *x: n->lst_childs) clean(x);
  delete(n);
}

static void print_tabs(int x){
  for(int i=0;i<x;i++) printf("  ");
}


class MCTS{
public:
  static Node* root;

  static void mcts(Board *board, int time_limit, bool player1);

  static double eval(Node *node, int tot);
  static int select_child(Node* node);
  static Node* select(Node* node);
  static void expand(Node* node);
  static int simulate(Board *board, bool player1, int depth_max);
  static void backpropagate(Node *node, int res);
  static void backpropagate_aux(Node *node, int win,int draw, bool player);

};

static void print_tree(Node *n, int tabs){
  return;
  if(tabs > 1)return;

  if(!n->has_childs()){
    print_tabs(tabs);
    printf("(----):\n");
    return;
  }
  print_tabs(tabs);
  if(n->parent) printf("(%.3lf,%d):\n",MCTS::eval(n,n->parent->games),(int)n->games);
  else printf("(--,%d):\n",(int)n->games);
  for(Node *a: n->lst_childs) print_tree(a,tabs+1);
}

#endif //MCTS_H
