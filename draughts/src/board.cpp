#include "board.h"

//unit vector for view segments
std::pair<int,int> unit_vector[] = {std::make_pair( 1,-1),
  std::make_pair( 0,-1),
  std::make_pair(-1,-1),
  std::make_pair(-1, 0)};


  //constructor
  Board::Board(){
    memset(board, 0, sizeof board);

    for(int a = 0; a < 8; a++){
      for(int b = 0; b < 8; b++){
        if(b < 3 && (b + a) % 2 == 0){
          board[a][b] = 1;
        }
        else if(b > 4 && (b + a)%2 == 0){
          board[a][b] = -1;
        }
        else{
          board[a][b] = 0;
        }
      }
    }

    depth = 0;
    //last_play.i = last_play.j = -1;
    //best_play.i = best_play.j = 0;
  }

  //play piece of player in column
  Pos Board::play(Pos p, int code){
    //[TODO] test if valid move



    int value = board[p.i][p.j];
    board[p.i][p.j] = 0;
    switch(code){
      case(0): p.i --;
      p.j ++; break; //step right up
      case(1): p.i ++;
      p.j ++; break; //step right down
      case(2): //jump right up
      board[p.i-1][p.j+1] = 0;
      p.i -= 2;
      p.j += 2; break;
      case(3): //jump right down
      board[p.i+1][p.j+1] = 0;
      p.i += 2;
      p.j += 2; break;
      case(4): p.i --;
      p.j --; break; //step left up
      case(5): p.i ++;
      p.j --; break; //step left down
      case(6): //jump left up
      board[p.i-1][p.j-1] = 0;
      p.i -= 2;
      p.j -= 2;  break;
      case(7): //jump left down
      board[p.i+1][p.j-1] = 0;
      p.i += 2;
      p.j -= 2;  break;
      default: break;
    }
    board[p.i][p.j] = value;
    if((p.j == 0 && value == -1) || (p.j == 7 && value == 1)){  //king it
      board[p.i][p.j] *= 2;
      last_up = true;
    }
    else last_up = false;

    last_play = p;
    last_code = code;

    return p;
  }


  //undo last play
  Pos Board::rmplay(Pos last_p, int last_c, bool last_u){
    //[TODO] test if removable

    Pos p = last_play;
    int code = last_code;
    bool up = last_up;

    last_play = last_p;
    last_code = last_c;
    last_up = last_u;

    int value = board[p.i][p.j];
    board[p.i][p.j] = 0;

    if(up) value /= 2;

    switch(code){
      case(0): p.i ++;
      p.j --; break; //step right up
      case(1): p.i --;
      p.j --; break; //step right down
      case(2): //jump right up
      p.i += 2;
      p.j -= 2;
      board[p.i-1][p.j+1] = 0;
      break;
      case(3): //jump right down
      p.i -= 2;
      p.j -= 2;
      board[p.i+1][p.j+1] = 0;
      break;
      case(4): p.i ++;
      p.j ++; break; //step left up
      case(5): p.i --;
      p.j ++; break; //step left down
      case(6): //jump left up
      p.i += 2;
      p.j += 2;
      board[p.i-1][p.j-1] = 0;
      break;
      case(7): //jump left down
      p.i -= 2;
      p.j += 2;
      board[p.i+1][p.j-1] = 0;
      break;
      default: break;
    }
    board[p.i][p.j] = value;

    return p;
  }

  // pos inside board
  bool Board::inBounds(Pos p){
    return p.i >= 0 && p.i < 8 && p.j >= 0 && p.j < 8;
  }

  // pos empty
  bool Board::open(Pos p){
    return inBounds(p) && board[p.i][p.j] == 0;
  }

  // test if piece p1 can jump piece p2
  bool Board::jumpOK(Pos p1, Pos p2){
    return open(mk_Pos(2*p2.i - p1.i,2*p2.j - p1.j)) && inBounds(p2) && (sign(board[p1.i][p1.j]) == -sign(board[p2.i][p2.j]));
  }

  bool Board::canJump(Pos p){
    int pieceType = board[p.i][p.j];
    if((pieceType > 0 || pieceType == -2) && (jumpOK(p, mk_Pos(p.i-1,p.j+1)) || jumpOK(p, mk_Pos(p.i+1,p.j+1)))){  //check jumps in the positive direction
      return true;
    }
    if((pieceType < 0 || pieceType == 2) &&(jumpOK(p, mk_Pos(p.i-1,p.j-1)) || jumpOK(p, mk_Pos(p.i+1,p.j-1)))){  //check jumps in the negative direction
      return true;
    }
    return false;
  }

  bool Board::canStep(Pos p){
    int pieceType = board[p.i][p.j];
    if((pieceType > 0 || pieceType == -2) && (open(mk_Pos(p.i-1,p.j+1)) || open(mk_Pos(p.i+1,p.j+1)))){  //check steps in the positive direction
      return true;
    }
    if((pieceType < 0 || pieceType == 2) &&(open(mk_Pos(p.i-1,p.j-1)) || open(mk_Pos(p.i+1,p.j-1)))){  //check steps in the negative direction
      return true;
    }
    return false;
  }

  std::vector<Pos> Board::getMovablePieces (bool player1){
    std::vector<Pos> res;
    Pos px;
    for(int i=0;i<8;i++){
      for(int j=0;j<8;j++){
        px.i = i, px.j = j;
        if(sign(board[i][j]) == (player1 ? 1 : -1) && canJump(px))
        res.push_back(px);
      }
    }

    if(res.empty()){
      for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
          px.i = i, px.j = j;
          if(sign(board[i][j]) == (player1 ? 1 : -1) && canStep(px))
          res.push_back(px);
        }
      }
    }

    return res;
  }

  int Board::gameEnd(){
    if(getMovablePieces(true).empty()) return -1;
    if(getMovablePieces(false).empty()) return 1;
    return 0;
  }

  std::vector<std::list<int> > Board::getJumpMoves(Pos p){
    std::vector<std::list<int> > moves;
    std::vector<std::list<int> > mx;
    int pieceType = board[p.i][p.j];

    Pos lp; int lc; bool up;
    Pos px;

    if(pieceType > 0 || pieceType == -2){
      if(jumpOK(p, mk_Pos(p.i-1,p.j+1))){
        //(2);

        lp = last_play; lc = last_code; up = last_up;
        px = play(p, 2);
        mx = getJumpMoves(px);
        rmplay(lp,lc,up);

        for(int i=0;i<(int)mx.size();i++){
          mx[i].push_front(2);
          moves.push_back(mx[i]);
        }

      }
      if(jumpOK(p, mk_Pos(p.i+1,p.j+1))){
        //(3);

        lp = last_play; lc = last_code; up = last_up;
        px = play(p, 3);
        mx = getJumpMoves(px);
        rmplay(lp,lc,up);

        for(int i=0;i<(int)mx.size();i++){
          mx[i].push_front(3);
          moves.push_back(mx[i]);
        }
      }
    }
    if(pieceType < 0 || pieceType == 2){
      if(jumpOK(p, mk_Pos(p.i-1,p.j-1))){
        //(6);

        lp = last_play; lc = last_code; up = last_up;
        px = play(p, 6);
        mx = getJumpMoves(px);
        rmplay(lp,lc,up);

        for(int i=0;i<(int)mx.size();i++){
          mx[i].push_front(6);
          moves.push_back(mx[i]);
        }
      }
      if(jumpOK(p, mk_Pos(p.i+1,p.j-1))){
        //(7);

        lp = last_play; lc = last_code; up = last_up;
        px = play(p, 7);
        mx = getJumpMoves(px);
        rmplay(lp,lc,up);

        for(int i=0;i<(int)mx.size();i++){
          mx[i].push_front(7);
          moves.push_back(mx[i]);
        }
      }
    }

    return moves;
  }

  std::vector<std::list<int> > Board::getStepMoves(Pos p){
    std::vector<std::list<int> > moves;
    int pieceType = board[p.i][p.j];

    if(pieceType > 0 || pieceType == -2){
      if(open(mk_Pos(p.i-1,p.j+1))){
        moves.push_back(std::list<int>());
        moves.back().push_back(0);
      }
      if(open(mk_Pos(p.i+1,p.j+1))){
        moves.push_back(std::list<int>());
        moves.back().push_back(1);
      }
    }
    if(pieceType < 0 || pieceType == 2){
      if(open(mk_Pos(p.i-1,p.j-1))){
        moves.push_back(std::list<int>());
        moves.back().push_back(4);
      }
      if(open(mk_Pos(p.i+1,p.j-1))){
        moves.push_back(std::list<int>());
        moves.back().push_back(5);
      }
    }

    return moves;
  }

  std::vector<std::list<int> > Board::getMoves(Pos p){
    if(canJump(p))
      return getJumpMoves(p);

    if(canStep(p))
      return getStepMoves(p);
  }

  /*

  //evaluate board
  int Board::eval_board(){
  int s = 0;
  int k0,k1,k2,k3;
  for(int i=0;i<3;i++){
  k0 = board[i][0]; k1 = board[i][1];
  k2 = board[i][2]; k3 = board[i][3];
  s += Eval::eval4[k0][k1][k2][k3];
}
for(int j=0;j<4;j++){
k0 = board[0][j]; k1 = board[1][j]; k2 = board[2][j];
s += Eval::eval3[k0][k1][k2];
}
k0 = board[0][0]; k1 = board[1][1]; k2 = board[2][2]; s += Eval::eval3[k0][k1][k2];
k0 = board[0][1]; k1 = board[1][2]; k2 = board[2][3]; s += Eval::eval3[k0][k1][k2];
k0 = board[0][2]; k1 = board[1][1]; k2 = board[2][0]; s += Eval::eval3[k0][k1][k2];
k0 = board[0][3]; k1 = board[1][2]; k2 = board[2][1]; s += Eval::eval3[k0][k1][k2];

return s;
}
*/

//print board pretty
void Board::print_board(){
  printf("Board:\n");
  printf("|-"); for(int i=0;i<8;i++)printf("--"); printf("-|\n");
  for(int i=0;i<8;i++){
    printf("| ");
    for(int j=0;j<8;j++){
      switch(board[i][j]){
        case -2:
        printf("B "); break;
        case -1:
        printf("b "); break;
        case 0:
        printf("_ "); break;
        case 1:
        printf("a "); break;
        case 2:
        printf("A "); break;
      }
    }
    printf(" |\n");
  }
  printf("|-"); for(int i=0;i<8;i++)printf("--"); printf("-|\n");
}
