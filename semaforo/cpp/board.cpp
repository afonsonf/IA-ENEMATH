#include "board.h"

//unit vector for view segments
std::pair<int,int> unit_vector[] = {
std::make_pair( 1,-1),
std::make_pair( 0,-1),
std::make_pair(-1,-1),
std::make_pair(-1, 0)};

//constructor
Board::Board(){
  //initialize board
  memset(board, 0, sizeof board);

  depth = 0;
}

//duplication
Board* Board::dup(){
  Board *dup = new Board();

  //copy ONLY board, stack of plays not needed
  for(int i=0;i<3;i++){
    for(int j=0;j<4;j++) dup->board[i][j] = board[i][j];
  }

  return dup;
}

//Play
void Board::play(Play p){
  //add play to the stack
  playsStack.push(p);

  //play it in the board
  board[p.i][p.j]++;
}

//undo last play
void Board::rmplay(){
  //remove play from stack
  Play last_play = playsStack.top();
  playsStack.pop();

  //undo play
  board[last_play.i][last_play.j]--;
}

//get playabale plays for player1
std::vector<Play> Board::getPlays(bool player){
  std::vector<Play> res;
  Play p;

  //add plays to res
  for(int i=0;i<3;i++){
    for(int j=0;j<4;j++){
      if(board[i][j]<=2){
        p.i = i, p.j = j;
        res.push_back(p);
      }
    }
  }

  return res;
}

bool Board::final_board(){
  if(playsStack.empty()) return false;

  Play last_play = playsStack.top();

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

//check whoWins
int Board::whoWins(bool next_player){
  //next player is false and loses return  1 (true wins)
  //next player is true  and loses return -1 (false wins)
  //else return 0

  if(final_board()){
    if(next_player) return -1;
    else return 1;
  }

  return 0;
}

//check if there is a draw
bool Board::isDraw(){
  if(getPlays(true).empty()) return true;
  return false;
}

bool Board::gameOver(bool next_player){
  if(whoWins(next_player) || isDraw()) return true;
  return false;
}

//evals board
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
