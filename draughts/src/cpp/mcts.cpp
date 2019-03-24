#include "mcts.h"

void MCTS::mcts(Board *board, int time_limit, bool player1){
  int start_time = clock();
  srand(time(NULL));

  node *root = new node(NULL,player1,0);
  node *n,*child;
  Board *dup1,*dup2;
  Pos pos;
  int res, win;

  while((clock() - start_time) < time_limit){
    //printf("%d %d\n",clock()-start_time,time_limit);
    dup1 = board->dup();
    //print_tree(root,0);
    n = select(root,dup1);

    expand(n,dup1);

    for(int i=0;i<(int)n->lst_childs.size();i++){
      dup2 = dup1->dup();
      child = n->lst_childs[i];

      //play moves
      pos = n->lst_pos[i];
      for(int code: n->lst_moves[i]) pos = dup2->play(pos,code);

      //simulate
      res = simulate(dup2,child->player1,80);

      //update wins/games
      win=0;
      if(child->player1 && res>0) win=1;
      else if(!child->player1 && res<0) win=1;

      //backpropagate
      backpropagate(child, win,true);

      free(dup2);
    }

    free(dup1);
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

  printf("%d %d\n",n->wins,n->games);

  free(dup1);clean(root);
}

node* MCTS::select(node *root, Board *board){
  if(!root){
    printf("Erro null\n");
    exit(1);
  }
  if(!root->has_childs()) return root;

  int best = root->best_child;

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

void MCTS::backpropagate(node *n, int win, bool player){
  if(!n->parent) return;

  if(player) n->wins+=win;
  n->games++;

  double val = n->wins*1.0/n->games * 100;
  if(n->parent->best_value > val){
    n->parent->best_value = val;
    n->parent->best_child = n->id;
  }

  backpropagate(n->parent,win,!player);
}
