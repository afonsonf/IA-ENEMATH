#include "board.h"

int values[8][8] = {
  {1, 1, 1, 4, 4, 6, 6, 8},
  {1, 1, 1, 4, 4, 6, 6, 8},
  {1, 1, 1, 4, 4, 6, 6, 8},
  {1, 1, 1, 4, 4, 6, 6, 8},
  {1, 1, 1, 4, 4, 6, 6, 8},
  {1, 1, 1, 4, 4, 6, 6, 8},
  {1, 1, 1, 4, 4, 6, 6, 8},
  {1, 1, 1, 4, 4, 6, 6, 8}
};

int valuestry[8][8] = {
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3}
};

int valuesKing[8][8] = {
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 3, 3, 3, 3, 1, 1},
  {1, 1, 3, 4, 4, 3, 1, 1},
  {1, 1, 3, 4, 4, 3, 1, 1},
  {1, 1, 3, 3, 3, 3, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1}
};

//constructor
Board::Board(){
  memset(board, 0, sizeof board);

  for(int a = 0; a < 8; a++){
    for(int b = 0; b < 8; b++){
      if(b < 3 && (b + a) % 2 == 0){
        board[a][b] = 1;
        numberPieces++;
      }
      else if(b > 4 && (b + a)%2 == 0){
        board[a][b] = -1;
        numberPieces++;
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

bool Board::validMove(Pos p, int code){
  if(!inBounds(p)){
    printf("Error: pos not in bounds (%d,%d)\n",p.i,p.j); return false;
  }
  if(open(p)){
    printf("Error: no piece in pos (%d,%d)\n",p.i,p.j); return false;
  }

  if(code == 0 && !open(mk_Pos(p.i-1,p.j+1))){
    printf("Error: try step right up, pos not open (%d,%d)\n",p.i,p.j); return false;
  }
  if(code == 1 && !open(mk_Pos(p.i+1,p.j+1))){
    printf("Error: try step right down, pos not open (%d,%d)\n",p.i,p.j); return false;
  }
  if(code == 4 && !open(mk_Pos(p.i-1,p.j-1))){
    printf("Error: try step left up, pos not open (%d,%d)\n",p.i,p.j); return false;
  }
  if(code == 5 && !open(mk_Pos(p.i+1,p.j-1))){
    printf("Error: try step left down, pos not open (%d,%d)\n",p.i,p.j); return false;
  }

  if(code == 2 && !jumpOK(p,mk_Pos(p.i-1,p.j+1))){
    printf("Error: try jump right up, jump not ok (%d,%d)\n",p.i,p.j); return false;
  }
  if(code == 3 && !jumpOK(p,mk_Pos(p.i+1,p.j+1))){
    printf("Error: try jump right down, jump not ok (%d,%d)\n",p.i,p.j); return false;
  }
  if(code == 6 && !jumpOK(p,mk_Pos(p.i-1,p.j-1))){
    printf("Error: try jump left up, jump not ok (%d,%d)\n",p.i,p.j); return false;
  }
  if(code == 7 && !jumpOK(p,mk_Pos(p.i+1,p.j-1))){
    printf("Error: try jump left down, jump not ok (%d,%d)\n",p.i,p.j); return false;
  }
  return true;
}

//play piece of player in column
Pos Board::play(Pos p, int code){
  //[TODO] test if valid move
  if(!validMove(p,code)){
    print_board(); exit(1);
  }

  int value = board[p.i][p.j];
  board[p.i][p.j] = 0;
  switch(code){
    case(0):{ //step right up
      p.i --; p.j ++;
      break;
    }
    case(1):{ //step right down
      p.i ++; p.j ++;
      break;
    }
    case(2):{ //jump right up

      last_eat = board[p.i-1][p.j+1];
      board[p.i-1][p.j+1] = 0;
      p.i -= 2; p.j += 2;
      numberPieces--;
      break;
    }
    case(3):{ //jump right down
      last_eat = board[p.i+1][p.j+1];
      board[p.i+1][p.j+1] = 0;
      p.i += 2; p.j += 2;
      numberPieces--;
      break;
    }
    case(4):{ //step left up
      p.i --; p.j --;
      break;
    }
    case(5):{ //step left down
      p.i ++; p.j --;
      break;
    }
    case(6):{ //jump left up
      last_eat = board[p.i-1][p.j-1];
      board[p.i-1][p.j-1] = 0;
      p.i -= 2; p.j -= 2;
      numberPieces--;
      break;
    }

    case(7):{ //jump left down
      last_eat = board[p.i+1][p.j-1];
      board[p.i+1][p.j-1] = 0;
      p.i += 2; p.j -= 2;
      numberPieces--;
      break;
    }
    default: printf("Error cod\n"); exit(1); break;
  }

  board[p.i][p.j] = value;
  if((p.j == 0 && value == -1) || (p.j == 7 && value == 1)){  //king it
    board[p.i][p.j] *= valueOfKing;
    last_up = true;
  }
  else last_up = false;

  last_play = p;
  last_code = code;

  return p;
}

//undo last play
Pos Board::rmplay(Pos last_p, int last_c, int last_e, bool last_u){
  //[TODO] test if removable

  Pos p = last_play;
  int code = last_code;
  int eat = last_eat;
  bool up = last_up;

  last_play = last_p;
  last_code = last_c;
  last_eat = last_e;
  last_up = last_u;

  int value = board[p.i][p.j];
  board[p.i][p.j] = 0;

  if(up) value /= valueOfKing;

  switch(code){
    case(0):{ //step right up
      p.i ++; p.j --;
      break;
    }
    case(1):{ //step right down
      p.i --; p.j --;
      break;
    }
    case(2):{ //jump right up
      p.i += 2; p.j -= 2;
      board[p.i-1][p.j+1] = eat;
      numberPieces++;
      break;
    }
    case(3):{ //jump right down
      p.i -= 2; p.j -= 2;
      board[p.i+1][p.j+1] = eat;
      numberPieces++;
      break;
    }
    case(4):{ //step left up
      p.i ++; p.j ++;
      break;
    }
    case(5):{ //step left down
      p.i --; p.j ++;
      break;
    }
    case(6):{ //jump left up
      p.i += 2; p.j += 2;
      board[p.i-1][p.j-1] = eat;
      numberPieces++;
      break;
    }
    case(7):{ //jump left down
      p.i -= 2; p.j += 2;
      board[p.i+1][p.j-1] = eat;
      numberPieces++;
      break;
    }
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
  if((pieceType > 0 || pieceType == -valueOfKing) && (jumpOK(p, mk_Pos(p.i-1,p.j+1)) || jumpOK(p, mk_Pos(p.i+1,p.j+1)))){  //check jumps in the positive direction
    return true;
  }
  if((pieceType < 0 || pieceType == valueOfKing) &&(jumpOK(p, mk_Pos(p.i-1,p.j-1)) || jumpOK(p, mk_Pos(p.i+1,p.j-1)))){  //check jumps in the negative direction
    return true;
  }
  return false;
}

bool Board::canStep(Pos p){
  int pieceType = board[p.i][p.j];
  if((pieceType > 0 || pieceType == -valueOfKing) && (open(mk_Pos(p.i-1,p.j+1)) || open(mk_Pos(p.i+1,p.j+1)))){  //check steps in the positive direction
    return true;
  }
  if((pieceType < 0 || pieceType == valueOfKing) &&(open(mk_Pos(p.i-1,p.j-1)) || open(mk_Pos(p.i+1,p.j-1)))){  //check steps in the negative direction
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

bool Board::gameOver(bool player1){
  if(getMovablePieces(player1).empty()) return true;
  return false;
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

  Pos lp; int lc, le; bool up;
  Pos px;

  if(pieceType > 0 || pieceType == -valueOfKing){
    if(jumpOK(p, mk_Pos(p.i-1,p.j+1))){
      //(2);

      lp = last_play; lc = last_code; le = last_eat; up = last_up;
      px = play(p, 2);
      mx = getJumpMoves(px);
      rmplay(lp,lc,le,up);

      if((int)mx.size() == 0){
        moves.push_back(std::list<int>());
        moves.back().push_back(2);
      }
      else {
        for(int i=0;i<(int)mx.size();i++){
          mx[i].push_front(2);
          moves.push_back(mx[i]);
        }
      }

    }
    if(jumpOK(p, mk_Pos(p.i+1,p.j+1))){
      //(3);

      lp = last_play; lc = last_code; le = last_eat; up = last_up;
      px = play(p, 3);
      mx = getJumpMoves(px);
      rmplay(lp,lc,le,up);

      if((int)mx.size() == 0){
        moves.push_back(std::list<int>());
        moves.back().push_back(3);
      }
      else {
        for(int i=0;i<(int)mx.size();i++){
          mx[i].push_front(3);
          moves.push_back(mx[i]);
        }
      }
    }
  }
  if(pieceType < 0 || pieceType == valueOfKing){
    if(jumpOK(p, mk_Pos(p.i-1,p.j-1))){
      //(6);

      lp = last_play; lc = last_code; le = last_eat; up = last_up;
      px = play(p, 6);
      mx = getJumpMoves(px);
      rmplay(lp,lc,le,up);

      if((int)mx.size() == 0){
        moves.push_back(std::list<int>());
        moves.back().push_back(6);
      }
      else {
        for(int i=0;i<(int)mx.size();i++){
          mx[i].push_front(6);
          moves.push_back(mx[i]);
        }
      }
    }
    if(jumpOK(p, mk_Pos(p.i+1,p.j-1))){
      //(7);

      lp = last_play; lc = last_code; le = last_eat; up = last_up;
      px = play(p, 7);
      mx = getJumpMoves(px);
      rmplay(lp,lc,le,up);

      if((int)mx.size() == 0){
        moves.push_back(std::list<int>());
        moves.back().push_back(7);
      }
      else {
        for(int i=0;i<(int)mx.size();i++){
          mx[i].push_front(7);
          moves.push_back(mx[i]);
        }
      }
    }
  }
  return moves;
}

std::vector<std::list<int> > Board::getStepMoves(Pos p){
  std::vector<std::list<int> > moves;
  int pieceType = board[p.i][p.j];

  if(pieceType > 0 || pieceType == -valueOfKing){
    if(open(mk_Pos(p.i-1,p.j+1))){
      moves.push_back(std::list<int>());
      moves.back().push_back(0);
    }
    if(open(mk_Pos(p.i+1,p.j+1))){
      moves.push_back(std::list<int>());
      moves.back().push_back(1);
    }
  }
  if(pieceType < 0 || pieceType == valueOfKing){
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

int Board::eval_board(){
  int value = 0;
  for(int i=0;i<8;i++){
    for(int j=0; j<8;j++){
      if(std::abs(board[i][j]) == valueOfKing)
        value += valuesKing[i][j] * board[i][j];
      else if(sign(board[i][j]) > 0){
        value += valuestry[i][j] * board[i][j];
        //printf("(%d,%d) val+ %d %d\n",i,j,values[i][j],board[i][j]);
      }
      else if(sign(board[i][j]) < 0){
        value += valuestry[i][7-j] * board[i][j];
        //printf("(%d,%d) val- %d %d\n",i,j,values[i][7-j],board[i][j]);
      }
    }
  }
  //printf("%d / %d\n",value, numberPieces);
  return value;
}


//print board pretty
void Board::print_board(){
  printf("Board: %d\n", eval_board());
  printf("|-"); for(int i=0;i<8;i++)printf("--"); printf("-|\n");
  for(int i=0;i<8;i++){
    printf("| ");
    for(int j=0;j<8;j++){
      switch(board[i][j]){
        case -valueOfKing:{printf("B "); break;}
        case -1:{printf("b "); break;}
        case  0:{printf("_ "); break;}
        case  1:{printf("r "); break;}
        case valueOfKing:{printf("R "); break;}

        default:
        printf("Error board: (%d,%d) %d\n",i,j,board[i][j]); exit(1);
      }
    }
    printf(" |\n");
  }
  printf("|-"); for(int i=0;i<8;i++)printf("--"); printf("-|\n\n");
}
