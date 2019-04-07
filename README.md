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

  !? void gameOver(bool player); <br>
  !? void gameEnd(); <br>

MCTS:
