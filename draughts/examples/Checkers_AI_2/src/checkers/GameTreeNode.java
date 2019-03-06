package checkers;

import board.BoardPosition;
import java.util.LinkedList;

/**
 * GameTreeNode: a point in a game tree
 * @author tim
 */
public class GameTreeNode {
    public LinkedList <GameTreeNode> children;  //the resulting possible moves
    public BoardPosition BP;  //the associated board position

    public GameTreeNode(BoardPosition BP){
        children = new LinkedList <GameTreeNode> ();
        this.BP = BP;
    }

    /**
     * moves through the tree until it reaches the end, where it sprouts an additional generation on all
     * @param player1  //who is in control at this level
     */
    public void sprout(boolean player1){
        for(GameTreeNode GTN : children){
            GTN.sprout(!player1);
        }

        if(children.isEmpty()){
            LinkedList <BoardPosition> moves = BP.getMoves(player1);
            for(BoardPosition b : moves){
                children.add(new GameTreeNode(b));  //add them all to the list
            }
        }
    }

    /**
     * returns the value of the best move in this part of the tree
     */
    public double minimax(boolean player1){
        if(children.isEmpty()){  //if this is as deep as it gets
            return BP.boardValue();
        }

        if(player1){  //if it is player1, we maximize the score
            double a = Double.MIN_VALUE;
            for(GameTreeNode GTN : children){  //cycle through all of the possible resulting moves
                a = Math.max(a, GTN.minimax(!player1));
            }
            return a;
        }
        else{   //if it is player 2, we minimize the score
            double a = Double.MAX_VALUE;
            for(GameTreeNode GTN : children){  //cycle through all of the possible resulting moves
                a = Math.min(a, GTN.minimax(!player1));
            }
            return a;
        }
    }

    public GameTreeNode getMove(boolean player1){
        if(children.isEmpty()){
            System.out.println("NO POSSIBLE MOVES");
            return null;
        }

        GameTreeNode best = null;
        if(player1){  //if we are player1, we want to maximize the board score
            double a = Double.MIN_VALUE;
            for(GameTreeNode GTN : children){  //cycle through all of the possible resulting moves
                double value = GTN.minimax(!player1);  //get the value of the taking the other move
                if(best == null || value > a){
                    a = value;
                    best = GTN;
                }
            }
        }
        else{  //if we are not player1, we want to minimize the board score
            double a = Double.MAX_VALUE;
            for(GameTreeNode GTN : children){  //cycle through all of the possible resulting moves
                double value = GTN.minimax(!player1);  //get the value of the taking the other move
                if(best == null || value < a){
                    a = value;
                    best = GTN;
                }
            }
        }
//        double maxScore = (player1 ? Double.MIN_VALUE : Double.MAX_VALUE);  //highest or lowest, depending on what we want
//        for(GameTreeNode GTN : children){
//            double value = GTN.minimax(!player1);
//            if(best == null || value * (player1 ? 1 : -1) > maxScore * (player1 ? 1 : -1)){
//                maxScore = value;
//                best = GTN;
//            }
//        }
        return best;
    }
}
