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
  bool Board::play(Pos p, int code){
    //[TODO] test if valid move

    last_play = p;
    last_code = code;

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
      p.j --; break; //step right up
      case(5): p.i ++;
      p.j --; break; //step right down
      case(6): //jump right up
      board[p.i-1][p.j-1] = 0;
      p.i -= 2;
      p.j -= 2;  break;
      case(7): //jump right down
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
  }


  //undo last play
  bool Board::rmplay(Pos last_p, int last_c){
    //[TODO] test if removable

    Pos p = last_play;
    int code = last_code;

    last_play = last_p;
    last_code = last_c;

    int value = board[p.i][p.j];
    board[p.i][p.j] = 0;

    if(last_up) value /= 2;
    last_up = false;

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
      p.j ++; break; //step right up
      case(5): p.i --;
      p.j ++; break; //step right down
      case(6): //jump right up
      p.i += 2;
      p.j += 2;
      board[p.i-1][p.j-1] = 0;
      break;
      case(7): //jump right down
      p.i -= 2;
      p.j += 2;
      board[p.i+1][p.j-1] = 0;
      break;
      default: break;
    }

    board[p.i][p.j] = value;
  }

  bool Board::inBounds(Pos p){
    return p.i >= 0 && p.i < 8 && p.j >= 0 && p.j < 8;
  }

  bool Board::open(Pos p){
    return inBounds(p) && board[p.i][p.j] == 0;
  }

  bool Board::jumpOK(Pos p1, Pos p2){
    return open(mk_Pos(2*p2.i - p1.i,2*p2.j - p1.j)) && inBounds(p2) && (sign(board[p1.i][p1.j]) == -sign(board[p2.i][p2.j]));
  }

  bool Board::canJump(Pos p){
    int peiceType = board[p.i][p.j];
    if((peiceType > 0 || peiceType == -2) && (jumpOK(p, mk_Pos(p.i-1,p.j+1)) || jumpOK(p, mk_Pos(p.i+1,p.j+1)))){  //check jumps in the positive direction
      return true;
    }
    if((peiceType < 0 || peiceType == 2) &&(jumpOK(p, mk_Pos(p.i-1,p.j-1)) || jumpOK(p, mk_Pos(p.i+1,p.j-1)))){  //check jumps in the negative direction
      return true;
    }
    return false;
  }

  bool Board::canStep(Pos p){
    int peiceType = board[p.i][p.j];
    if((peiceType > 0 || peiceType == -2) && (open(mk_Pos(p.i-1,p.j+1)) || open(mk_Pos(p.i+1,p.j+1)))){  //check steps in the positive direction
      return true;
    }
    if((peiceType < 0 || peiceType == 2) &&(open(mk_Pos(p.i-1,p.j-1)) || open(mk_Pos(p.i+1,p.j-1)))){  //check steps in the negative direction
      return true;
    }
    return false;
  }
  
  /*
  bool Board::final_board(){
  int ix = last_play.i, jx = last_play.j;
  if(ix == -1 || jx == -1) return false;

  int v0,v1;
  int s, x; int i, j;

  x = board[ix][jx];
  if(x == 0) return false;

  for(int k=0;k<4;k++){
  v0 = unit_vector[k].first;
  v1 = unit_vector[k].second;

  s = 0;
  for(int m=1;m<3;m++){
  i = ix+m*v0; j = jx+m*v1;
  if(i<0 || j<0 || i>2 || j>3) break;
  if(x == board[i][j]) s++;
  else break;
}
v0 = -v0, v1 = -v1;
for(int m=1;m<3;m++){
i = ix+m*v0; j = jx+m*v1;
if(i<0 || j<0 || i>2 || j>3) break;
if(x == board[i][j]) s++;
else break;
}

if(s>=2) return true;
}

return false;
}

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

//print board pretty
void Board::print_board(){
printf("__");
for(int i=0;i<4;i++) printf("|_%d_", i);
printf("\n");
for(int i=0;i<3;i++){
printf("%d |",i);
for(int j=0;j<4;j++) printf(" %d  ", board[i][j]);
printf("\n");
}
}
*/
