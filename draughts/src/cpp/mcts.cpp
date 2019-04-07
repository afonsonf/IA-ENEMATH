#include "mcts.h"

const double EXPLOR_PARAM = 0.52026009502; //1.41421356237
node* MCTS::papi;

void MCTS::mcts(Board *board, int time_limit, bool player1){
  clock_t start_time = clock();
  srand(time(NULL));

  node *root = new node(NULL,player1,0,board->dup());
  expand(root);

  papi = root;

  node *child;
  Board *dup1;
  Pos pos;
  int res;

  while((clock() - start_time) < time_limit){
    //printf("%d %d\n",clock()-start_time,time_limit);

    child = select(root);
    expand(child);

    //simulate
    dup1 = child->board->dup();
    res = simulate(dup1,child->next_player,50);

    //backpropagate
    if(child->next_player && res>0){
      backpropagate(child, 2, 0, true);
    }
    else if(!child->next_player && res<0){
      backpropagate(child, 2, 0, true);
    }
    else if(!res){
      backpropagate(child, 0, 1, true);
    }
    else {
      backpropagate(child, 2, 0, false);
    }

    delete(dup1);
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

  //printf("n games: %d\n",root->games);

  clean(root);
}


double MCTS::eval(node *n,int tot){
  if(!n->has_childs()){
    return 0.5 + EXPLOR_PARAM*sqrt(log(tot+1));
  }

  double wr = n->wins/((double)n->games*2+1);
  if(papi->next_player!=n->next_player) wr = 1.0-wr;
  return wr + EXPLOR_PARAM*sqrt(log(tot+1)/((double)n->games+1));
}

int MCTS::select_child(node* n){
  int sz = (int)n->lst_childs.size();
  int best_i = 0;
  double best_value = 0,val;

  for(int i=0;i<sz;i++){
    val = eval(n->lst_childs[i],n->games);
    if(val>best_value){
      best_value = val;
      best_i = i;
    }
  }

  return best_i;
}

node* MCTS::select(node *node){
  if(!node){
    printf("Erro null\n");
    exit(1);
  }
  if(!node->has_childs()) return node;

  int best = select_child(node);

  return select(node->lst_childs[best]);
}

void MCTS::expand(node *n){
  Board *dup;

  n->lst_plays = n->board->getPlays(n->next_player);
  for(int i=0;i<(int)n->lst_plays.size();i++){
    dup = n->board->dup();
    dup->play(n->lst_plays[i]);
    n->lst_childs.push_back(new node(n,!n->next_player,i,dup));
  }
}

int MCTS::simulate(Board *board, bool player1, int depth_max){
  int end = board->gameEnd();
  if(end) return end;
  if(!depth_max) return 0;

  int r;

  auto plays = board->getPlays(player1);

  //random play
  r = rand() % (int) plays.size();
  Play p = plays[r];

  board->play(p);

  return simulate(board,!player1,depth_max-1);
}

void MCTS::backpropagate(node *n, int win, int draw, bool player){
  if(!n->parent){
    n->games++;
    return;
  }

  if(player) n->wins+=win;
  if(draw) n->wins++;
  n->games+=1;

  backpropagate(n->parent,win,draw,!player);
}
