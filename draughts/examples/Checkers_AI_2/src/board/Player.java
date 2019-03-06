package board;

import java.awt.event.*;

/**
 * Player: someone playing the game who makes descisions on their move
 * @author tim
 */
public abstract interface Player {
    public BoardPosition getMove();  //returns the next state
    public void update(BoardPosition BP, boolean player1);
    public void onMousePressed(MouseEvent e);
    public void onMouseReleased(MouseEvent e);
}
