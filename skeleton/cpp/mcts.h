#ifndef MCTS_H
#define MCTS_H

#include <time.h>
#include <math.h>
#include <algorithm>

#include "play.h"
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

static void clean(Node *node){
  if(!node) return;

  for(Node *x: node->lst_childs) clean(x);
  delete(node->board);
  delete(node);
}


class MCTS{
public:
  int time_limit;
  bool first_player;

  Node* root;
  Board *board;

  MCTS(int time_limit, bool first_player);

  void init(Board *board);

  void search();
  void play(Play p);

  double eval(Node *node, int tot);
  int select_child(Node* node);
  Node* select(Node* node);
  void expand(Node* node);
  int simulate(Board *board, bool player1, int depth_max);
  void backpropagate(Node *node, int res);
  void backpropagate_aux(Node *node, int win,int draw, bool player);

};
/*
static void print_tabs(int x){
  for(int i=0;i<x;i++) printf("  ");
}

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
*/
#endif //MCTS_H
