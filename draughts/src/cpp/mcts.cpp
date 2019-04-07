#include "mcts.h"

const double EXPLOR_PARAM = 1.41421356237; //1.41421356237 //0.52026009502

MCTS::MCTS(){}

void MCTS::init(Board *board, int time_limit, bool player1){
  clean(root);

  this->root = new Node(NULL, player1, board->dup());
  expand(this->root);
  this->time_limit = time_limit;
  this->board = board;
}

void MCTS::play(Play p){
  srand(time(NULL));

  Node *child;
  int i = 0;

  for(Play x: root->lst_plays){
    if(x == p) break;
    i++;
  }
  if(i == root->lst_plays.size()){
    printf("MCTS::play play not found\n");
    exit(1);
  }

  child = root->lst_childs[i];
  root->lst_childs[i] = NULL;

  clean(root);
  root = child;
  root->parent = NULL;

  if(!root->has_childs()) expand(root);
}

void MCTS::search(){
  clock_t start_time = clock();

  Node *child;
  Board *dup;
  Pos pos;
  int res;

  while((clock() - start_time) < time_limit){
    child = select(root);
    expand(child);

    for(int i=0;i<1;i++){
      //simulate
      dup = child->board->dup();
      res = simulate(dup,child->next_player,80);

      //backpropagate
      backpropagate(child, res);

      delete(dup);
    }

  }

  int best_i = 0;
  double best_wr = 1;
  int sz = (int)root->lst_childs.size();

  for(int i=0;i<sz;i++){
    child = root->lst_childs[i];
    if((child->wins*1.0/child->games) < best_wr){
        best_i = i;
        best_wr = (child->wins*1.0/child->games);
    }
  }

  board->best_play = root->lst_plays[best_i];

}


double MCTS::eval(Node *node,int tot){
  if(!node->has_childs()){
    return 0.5 + EXPLOR_PARAM*sqrt(log(tot+1));
  }

  double wr = node->wins/((double)node->games*2+1);
  if(root->next_player!=node->next_player) wr = 1.0-wr;
  return wr + EXPLOR_PARAM*sqrt(log(tot+1)/((double)node->games+1));
}

int MCTS::select_child(Node* node){
  int sz = (int)node->lst_childs.size();
  int best_i = 0;
  double best_value = 0,val;

  for(int i=0;i<sz;i++){
    val = eval(node->lst_childs[i],node->games);
    if(val>best_value){
      best_value = val;
      best_i = i;
    }
  }

  return best_i;
}

Node* MCTS::select(Node *node){
  if(!node){
    printf("Erro null\n");
    exit(1);
  }
  if(!node->has_childs()) return node;

  int best = select_child(node);
  return select(node->lst_childs[best]);
}

void MCTS::expand(Node *node){
  Board *dup;

  node->lst_plays = node->board->getPlays(node->next_player);
  for(int i=0;i<(int)node->lst_plays.size();i++){
    dup = node->board->dup();
    dup->play(node->lst_plays[i]);
    node->lst_childs.push_back(new Node(node,!node->next_player,dup));
  }
}

int MCTS::simulate(Board *board, bool player1, int depth_max){
  int end = board->gameEnd();
  if(end) return end;
  if(!depth_max) return 0;

  int r;

  auto plays = board->getPlays(player1);

  //random play
  std::random_shuffle(plays.begin(), plays.end());
  r = rand() % (int) plays.size();
  Play p = plays[r];

  board->play(p);

  return simulate(board,!player1,depth_max-1);
}

void MCTS::backpropagate_aux(Node *node, int win, int draw, bool player){
  if(!node->parent){
    node->games++;
    return;
  }

  if(player) node->wins+=win;
  if(draw) node->wins++;
  node->games+=1;

  backpropagate_aux(node->parent,win,draw,!player);
}

void MCTS::backpropagate(Node *node, int res){
  if(node->next_player && res>0){
    backpropagate_aux(node, 2, 0, true);
  }
  else if(!node->next_player && res<0){
    backpropagate_aux(node, 2, 0, true);
  }
  else if(!res){
    backpropagate_aux(node, 0, 1, true);
  }
  else {
    backpropagate_aux(node, 2, 0, false);
  }
}
