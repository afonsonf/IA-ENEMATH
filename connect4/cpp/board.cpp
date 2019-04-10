#include "board.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

//unit vector for view segments
std::pair<int,int> unit_vector[] = {std::make_pair( 1,-1),
									std::make_pair( 0,-1),
									std::make_pair(-1,-1),
									std::make_pair(-1, 0)};

//constructor
Board::Board(){
	MyBoost::load_boost();

	//initialize board
	for(int i=0;i<6;i++){
		for(int j=0;j<7;j++)
			this->board[i][j]=3;
		this->np[i]=0;
	}
	this->np[6]=0;//number of pieces

	this->depth = 0;
}

//duplication
Board* Board::dup(){
  Board *dup = new Board();

  //stack of plays not needed
	for(int i=0;i<6;i++){
		for(int j=0;j<7;j++) dup->board[i][j] = board[i][j];
	}
	for(int i=0;i<7;i++) dup->np[i] = np[i];

	if(!playsStack.empty())dup->playsStack.push(playsStack.top());

  return dup;
}

//Play
void Board::play(Play p){
  //add play to the stack
	playsStack.push(p);
	int player;
	if(p.player) player = 2;
	else player = 1;

  //play it in the board
	this->board[5-this->np[p.col]][p.col]=player;
	this->np[p.col]++;
}

//undo last play
void Board::rmplay(){
	if(playsStack.empty()) return;

  //remove play from stack
	Play p = playsStack.top();
	playsStack.pop();

  //undo play
	this->board[5-(this->np[p.col]-1)][p.col]=3;
	this->np[p.col]--;
}

//pos i,j, i starting at 0 from bottom, j start from 0, from left
int Board::pos(int i,int j){
	//test if valid indexes
	if(j<0 || j>6 || i<0 || i>5){
		printf("Error: pos out of board! %d %d\n",i,j);
		exit(1);
	}
	return this->board[5-i][j];
}

//get playabale plays for player1
std::vector<Play> Board::getPlays(bool player){
  std::vector<Play> res;

	Play p;

  //add plays to res
	for(int i=0;i<7;i++){
		if(np[i]<6){
			p.col = i, p.player = player;
			p.isnull = false;
			res.push_back(p);
		}
	}

  return res;
}

//test if game end
//-1 - 1 wins
//1  - 2 wins
//else 0
int Board::final_board(){
	if(playsStack.empty()) return 0;

	Play last = playsStack.top();
	int last_play = last.col;

	//if column empty, game not over
	if(this->np[last_play]==0) return -1;


	int flag=0;//test if board full
	for(int i=0;i<7;i++)
		if(np[i]!=6){
			flag=1;
			break;
		}

	//last piece played
	int x = this->pos(this->np[last_play]-1,last_play);
	int s,i=this->np[last_play]-1,j=last_play,ix,jx;
	//test if segment of at leat 4
	for(int k=0;k<4;k++){
		s=0;
		ix = i;jx=j;
		ix-=unit_vector[k].first;
		jx-=unit_vector[k].second;
		while(ix>=0 && ix<6 && jx>=0 && jx<7){
			if(pos(ix,jx)!=x)break;
			s++;
			ix-=unit_vector[k].first;
			jx-=unit_vector[k].second;
		}
		ix = i;jx=j;
		ix+=unit_vector[k].first;
		jx+=unit_vector[k].second;
		while(ix>=0 && ix<6 && jx>=0 && jx<7){
			if(pos(ix,jx)!=x)break;
			s++;
			ix+=unit_vector[k].first;
			jx+=unit_vector[k].second;
		}
		s++;
		if(s>=4)return (x == 1) ? -1 : 1;//player x wins
	}

	return 0;
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
	for(int i=0;i<7;i++) if(np[i]!=6) return false;
  return true;
}

bool Board::gameOver(bool next_player){
  if(whoWins(next_player) || isDraw()) return true;
  return false;
}

//evals board
int Board::eval_board(){
	int val = 0,temp;
	int col[7],dgp[6],dgn[6];
	for(int i=0;i<6;i++){
		dgp[i]=0;//positive diagonal
		dgn[i]=0;//negative diagonal
		col[i]=0;//column
	}
	col[6]=0;
	for(int i=5;i>=0;i--){
		temp = 0;
		for(int j=0;j<7;j++){
			temp=temp*10+this->board[i][j];
			col[j] = col[j]*10+this->board[i][j];

			if((i+j-3)>=0 && (i+j-3)<6){
				dgp[i+j-3] = dgp[i+j-3]*10+this->board[i][j];
			}

			if((j-i+2)>=0 && (j-i+2)<6){
				dgn[j-i+2] = dgn[j-i+2]*10+this->board[i][j];
			}

		}
		val+=Global::m7[temp];
	}

	for(int i=0;i<6;i++){
		if(dgp[i]<10000){
			val+=Global::m4[dgp[i]];
		}
		else if(dgp[i]<100000){
			val+=Global::m5[dgp[i]];
		}
		else if(dgp[i]<1000000){
			val+=Global::m6[dgp[i]];
		}

		if(dgn[i]<10000){
			val+=Global::m4[dgn[i]];
		}
		else if(dgn[i]<100000){
			val+=Global::m5[dgn[i]];
		}
		else if(dgn[i]<1000000){
			val+=Global::m6[dgn[i]];
		}
		val+=Global::m6c[col[i]];
	}
	val+=Global::m6c[col[6]];
	int player = playsStack.top().player;
	int x = (player)? 2 : 1;
	if(x==1) val+=16;
	else     val-=16;
	return val;
}

//print board pretty
void Board::print_board(){
	int x;
	for(int i=0;i<17;i++) printf("*");
	printf("\n");
	for(int i=5;i>=0;i--){
		printf("* ");
		for(int j=0;j<7;j++){
			x = pos(i,j);
			switch(x){
				case 3:
					printf("- ");
					break;
				case 1:
					printf(ANSI_COLOR_RED "O " ANSI_COLOR_RESET);
					break;
				case 2:
					printf(ANSI_COLOR_YELOW "X " ANSI_COLOR_RESET);
					break;
			}
		}
		printf("*");
		printf("\n");
	}
	for(int i=0;i<17;i++) printf("*");
	printf("\n  ");
	for(int i=0;i<7;i++) printf("%d ",i);
	printf("\n\n");
}
