# IA-ENEMATH
Workshop ENEMath

[WIP]

implementation of minimax (with alphabeta prunning) and mcts in c++ and python for 2 player board games.

to use the implementation of the minimax and mcts its only needed to implement the board with the at least the following mandatory methods:

Minimax:
  void play(Play p);
  void rmPlay(Play p);
  void gameOver(bool player);
  int eval_board();
MCTS:
