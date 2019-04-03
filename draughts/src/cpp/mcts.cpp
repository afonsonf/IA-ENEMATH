#include "mcts.h"

const double EXPLOR_PARAM = 1.3;



void MCTS::mcts(Board *board, int time_limit, bool player1){
  int start_time = clock();
  srand(time(NULL));

  node *root = new node(NULL,player1,0);
  expand(root,board);

  node *n, *child;
  Board *dup1;
  Pos pos;
  int res;

  while((clock() - start_time) < time_limit){
    //printf("%d %d\n",clock()-start_time,time_limit);
    dup1 = board->dup();
    //print_tree(root,0);
    n = select(root,dup1);

    expand(n,dup1);

    //simulate
    res = simulate(dup1,n->player1,120);

    //backpropagate
    if(child->player1 && res>0){
      backpropagate(n, 2, 0, true);
    }
    else if(!n->player1 && res<0){
      backpropagate(n, 2, 0, true);
    }
    else if(!res){
      backpropagate(n, 0, 1, true);
    }
    else {
      backpropagate(n, 2, 0, false);
    }

    delete(dup1);

  }


  dup1 = board->dup();
  n = select(root,dup1);

  if(!n->parent){
    printf("Erro arvore!\n");exit(1);
  }

  while(true){
    if(n->parent->parent) n = n->parent;
    else break;
  }


  board->best_code = n->parent->lst_moves[n->id];
  board->best_pos = n->parent->lst_pos[n->id];

  //printf("%d %d\n",n->wins,n->games);

  print_tree(root,0);
  //printf("nr games: %d\n",root->games);

  delete(dup1);clean(root);
}

double MCTS::eval(node *n,int tot,bool p){
  if(!n->has_childs()){
    return 0.5 + EXPLOR_PARAM*sqrt(log(tot+1));
  }

  double wr = n->wins/((double)n->games*2+1);
  if(p!=n->player1) wr = 1.0-wr;
  return wr + EXPLOR_PARAM*sqrt(log(tot+1)/((double)n->games+1));
}

int MCTS::select_child(node* n, bool p){
  int sz = (int)n->lst_childs.size();
  int best_i = 0;
  double best_value = 0,val;

  for(int i=0;i<sz;i++){
    val = eval(n->lst_childs[i],n->games,p);
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

  int best = select_child(root,root->player1);

  //printf("h %d %d\n",best,(int)root->lst_pos.size());

  Pos pos = root->lst_pos[best];
  for(int code: root->lst_moves[best]) pos = board->play(pos,code);

  return select(root->lst_childs[best], board);
}

void MCTS::expand(node *n, Board *board){
  std::vector<Pos> pieces = board->getMovablePieces(n->player1);
  std::vector<std::list<int> > moves;
  int i = 0;
  for(Pos p : pieces){
    moves = board->getMoves(p);
    for(std::list<int> codes: moves){
      n->lst_pos.push_back(p);
      n->lst_moves.push_back(codes);
      n->lst_childs.push_back(new node(n,!n->player1,i));
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
  if(!n){
    //n->games++;
    return;
  }

  if(player) n->wins+=win;
  if(draw) n->wins++;
  n->games+=1;

  backpropagate(n->parent,win,draw,!player);
}
