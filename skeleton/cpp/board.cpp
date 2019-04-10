#include "board.h"

//constructor
Board::Board(){
  //initialize board
}

//duplication
Board* Board::dup(){
  Board *dup = new Board();
  if(!playsStack.empty()) dup->playsStack.push(playsStack.top());
  //copy board

  return dup;
}

//Play
void Board::play(Play p){
  //add play to the stack
  //play it in the board
}

//undo last play
void Board::rmplay(){
  //remove play from stack
  //undo play
}

//get playabale plays for player1
std::vector<Play> Board::getPlays(bool player){
  std::vector<Play> res;

  //add plays to res

  return res;
}

//check whoWins
int Board::whoWins(bool next_player){
  //next player is false and loses return  1 (true wins)
  //next player is true  and loses return -1 (false wins)
  //else return 0
  return 0;
}

//check if there is a draw
bool Board::isDraw(){
  return false;
}

bool Board::gameOver(bool next_player){
  if(whoWins(next_player) || isDraw()) return true;
  return false;
}

//evals board
int Board::eval_board(){
  return 0;
}

//print board pretty
void Board::print_board(){

}
