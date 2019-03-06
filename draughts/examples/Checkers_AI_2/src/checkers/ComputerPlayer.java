package checkers;

import board.Player;
import board.BoardPosition;
import java.awt.event.*;

/**
 *
 * @author tim
 */
public class ComputerPlayer implements Player{

    public GameTreeNode myTree;  //the futuristic structure
    public boolean player1;  //if the computer is player 1
    int depth;

    public ComputerPlayer(BoardPosition BP, int Depth, boolean player1){
        myTree = new GameTreeNode(BP);
        this.player1 = player1;
        this.depth = Depth;
        while(Depth > 0){  //predict future moves
            myTree.sprout(true);  //start it off with the first player's
            Depth --;
        }
    }

    @Override
    public BoardPosition getMove(){

//        try{Thread.sleep(3000);}catch(Exception e){} //wait for click
        return myTree.getMove(player1).BP;  //tell it to become the next node down in its minimax list
    }

    @Override
    public void update(BoardPosition BP, boolean player1){
        
        String currentBoard = BP.toString();
        boolean switched = false;
        int a = 0;
        while(a < myTree.children.size() && !switched){
            if((myTree.children.get(a).BP.toString()).equals(currentBoard)){  //if we found a match
                myTree = myTree.children.get(a);
                switched = true;
            }
            a++;
        }

        if(!switched){  //if we can't find it in the tree (weird, this shouldn't happen)
//            System.out.println("Could not find move in the Game Tree, creating new tree structure COMP");
//            System.out.println("PRINTING WHAT I THOUGHT THE MOVES WERE");
//            for(GameTreeNode GTN : myTree.children){
//                System.out.println(GTN.BP);
//            }
            myTree = new GameTreeNode(BP);
            for(int b = 0; b < depth - 1; b++){
                myTree.sprout(!player1);
            }
        }
        myTree.sprout(!player1);
    }

    public void onMousePressed(MouseEvent e){
    }
    public void onMouseReleased(MouseEvent e){}
}
