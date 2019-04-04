#include "mcts.h"

const double EXPLOR_PARAM = 0.5;
node* MCTS::papi;

void MCTS::mcts(Board *board, int time_limit, bool player1){
  int start_time = clock();
  srand(time(NULL));

  node *root = new node(NULL,player1,0);
  papi = root;
  expand(root,board);

  node *child;
  Board *dup1;
  Pos pos;
  int res;

  while((clock() - start_time) < time_limit){
    //printf("%d %d\n",clock()-start_time,time_limit);

    dup1 = board->dup();
    child = select(root,dup1);
    expand(child,dup1);

    //simulate
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

  dup1 = board->dup();
    child = select(root,dup1);

    if(!child->parent){
      printf("Erro arvore!\n");exit(1);
    }

    while(true){
      if(child->parent->parent) child = child->parent;
      else break;
    }

    board->best_code = child->parent->lst_moves[child->id];
    board->best_pos = child->parent->lst_pos[child->id];

    delete(dup1);clean(root);
}
/*
int best_i = 0, most_plays, most_wins;
int sz = (int)root->lst_childs.size();

for(int i=0;i<sz;i++){
  child = root->lst_childs[i];
  if(child->wins > most_wins){
      best_i = i;
      most_plays = child->games;
      most_wins = child->wins;
  }
  else if(child->games > most_plays && child->wins == most_wins){
    best_i = i;
    most_plays = child->games;
  }
}
board->best_code = root->lst_moves[best_i];
board->best_pos = root->lst_pos[best_i];

clean(root);
---------------------------------------------------------------------------
dup1 = board->dup();
  child = select(root,dup1);

  if(!child->parent){
    printf("Erro arvore!\n");exit(1);
  }

  while(true){
    if(child->parent->parent) child = child->parent;
    else break;
  }

  board->best_code = child->parent->lst_moves[child->id];
  board->best_pos = child->parent->lst_pos[child->id];

  delete(dup1);clean(root);
*/

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

node* MCTS::select(node *root, Board *board){
  if(!root){
    printf("Erro null\n");
    exit(1);
  }
  if(!root->has_childs()) return root;

  int best = select_child(root);

  //printf("h %d %d\n",best,(int)root->lst_pos.size());

  Pos pos = root->lst_pos[best];
  for(int code: root->lst_moves[best]) pos = board->play(pos,code);

  return select(root->lst_childs[best], board);
}

void MCTS::expand(node *n, Board *board){
  std::vector<Pos> pieces = board->getMovablePieces(n->next_player);
  std::vector<std::list<int> > moves;
  int i = 0;
  for(Pos p : pieces){
    moves = board->getMoves(p);
    for(std::list<int> codes: moves){
      n->lst_pos.push_back(p);
      n->lst_moves.push_back(codes);
      n->lst_childs.push_back(new node(n,!n->next_player,i));
      i++;
    }
  }
}

int MCTS::simulate(Board *board, bool player1, int depth_max){
  int end = board->gameEnd();
  if(end) return end;
  if(!depth_max) return 0;

  int r;

  std::vector<Pos> pieces = board->getMovablePieces(player1);

  //random piece
  r = rand() % (int) pieces.size();
  Pos p = pieces[r];

  std::vector<std::list<int> > moves = board->getMoves(p);

  //random moves
  r = rand() % (int) moves.size();
  std::list<int> codes = moves[r];

  for(int code: codes) p = board->play(p,code);

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
