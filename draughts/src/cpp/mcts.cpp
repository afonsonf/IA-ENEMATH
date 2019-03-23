#include "mcts.h"

void MCTS::mcts(Board *board, bool player1, int time_limit){
  //start time = something
  node *root = new node(NULL,player1);
  node *n;
  Board *dup1,*dup2;
  Pos pos;
  double val;

  while(true){
    dup1 = board->dup();
    n = select(root,dup1);

    expand(n,dup1);

    for(int i=0;i<(int)n->lst_childs.size();i++){
      dup2 = dup1->dup();

      //play moves
      pos = n->lst_pos[i];
      for(int code: n->lst_moves[i]) pos = dup2->play(pos,code);

      //simulate
      val = simulate(dup2,!n->player1,80);

      //update wins/games

      //see if best child

      free(dup2);
    }

    //backpropagate

    free(dup1);
  }

  //select and save move in board
}

node* MCTS::select(node *root, Board *board){
  if(!root->has_childs()) return root;

  int best = root->best_child;
  Pos pos = root->lst_pos[best];
  for(int code: root->lst_moves[best]) pos = board->play(pos,code);

  return select(root->lst_childs[best], board);
}

void MCTS::expand(node *n, Board *board){
  std::vector<Pos> pieces = board->getMovablePieces(n->player1);
  std::vector<std::list<int> > moves;

  for(Pos p : pieces){
    moves = board->getMoves(p);
    for(std::list<int> codes: moves){
      n->lst_pos.push_back(p);
      n->lst_moves.push_back(codes);
      n->lst_childs.push_back(new node(n,!n->player1));
    }
  }
}

int MCTS::simulate(Board *board, bool player1, int depth_max){

}
