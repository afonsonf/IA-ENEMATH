package board;

import java.util.LinkedList;

import checkers.*;

/**
 * Game: runs the show
 * @author tim
 */
public class Game {

    public BoardViewer myViewer;
    public BoardPosition gameState;
    public Player RED;
    public Player BLACK;
    public boolean player1;  //true if RED is active player

    public Game(){
        int height = 700;
        int width = 600;

        LinkedList <String> records = new LinkedList <String> ();

        player1 = true;
        gameState = new BoardPosition();
        myViewer = new BoardViewer(10, width, height, this);
        // RED = new ComputerPlayer(gameState, 2, player1);
        RED = new RealPlayer(gameState, player1);
        BLACK = new ComputerPlayer(gameState, 6, !player1);
        // BLACK = new RealPlayer(gameState, !player1);


        while(!gameState.gameOver(player1)){ //&& !records.contains(gameState.toString())){
            records.add(gameState.toString());
            gameState = (player1 ? RED.getMove() : BLACK.getMove());
            RED.update(gameState, player1);
            BLACK.update(gameState, player1);
            player1 = !player1;

        }
        System.out.println("GAME OVER");
    }
}
