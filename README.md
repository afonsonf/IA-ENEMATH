# IA-ENEMATH
Workshop ENEMath

[WIP]

Implementation of minimax (with alphabeta prunning) and mcts in c++ and python for 2 player board games.

To use the implementation in the skeleton folder of the minimax and mcts you need at least to implement the methods that are in board and play files :

#### Play: <br>
Where a play is defined. This struct needs to have all information needed to perform a play.

* <b> operator==() ||  \__eq__() </b> <br>
overload of the method for testing equality of 2 plays.

* <b> printPlay(Play p) </b> <br>
print an play in one line (for default Human player)

#### Board: <br>
Where the board is defined.

*  <b> constructor </b> <br>
Initializes the board.

*  <b> play(Play p) </b>


Summary of the methods:
