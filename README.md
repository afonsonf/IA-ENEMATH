# IA-ENEMATH
Workshop ENEMath

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

*  <b> dup() </b> <br>
Return a copy of board.

* <b> play(Play p) </b> <br>
Do the play p.

* <b> rmplay(Play p)</b> <br>
Undo the play p.

* <b> getPlays(player) </b> <br>
Returns a vector/list of possible plays for player.

* <b> whoWins(next_player)</b> <br>
If next player wins and (next_player == True) returns 1. <br>
If next player wins and (next_player == False) returns -1. <br>
Else return 0.

* <b> isDraw() </b> <br>
Return True if is draw.

* <b> gameOver(next_player) </b> <br>
Returns true if game is over.

* <b> eval_board() </b> <br>
Returns the value of board, (positive if in favor of True player).

* <b> print_board() </b> <br>
Prints the board pretty.
