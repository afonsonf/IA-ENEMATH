# IA-ENEMATH
Workshop ENEMath

[WIP]

Implementation of minimax (with alphabeta prunning) and mcts in c++ and python for 2 player board games.

To use the implementation of the minimax and mcts its needed to implement the board.cpp with the at least the following mandatory methods:

Minimax:
  vector<Plays> getPlays(bool player); <br>
  void play(Play p); <br>
  void rmPlay(Play p); <br>
  int eval_board(); <br>

  bool gameOver(); someone win or draw <br>
  bool whoWins(); 1 if true wins, -1 if false wins <br> 

  void draw(); <br>

MCTS:
