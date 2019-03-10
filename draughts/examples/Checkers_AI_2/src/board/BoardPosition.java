package board;

import java.util.LinkedList;
import java.util.Random;

/**
 * BoardPosition, a unique representation of the checkers board
 * @author tim
 */
public class BoardPosition {
    public int[][] board;  //the usable squares on the board  0 is open, 1 is player 1, -1 is player 2, K is 1 or -1 * 2

    public BoardPosition(){
        board = new int[8][8];
        for(int a = 0; a < board.length; a++){
            for(int b = 0; b < board[0].length; b++){
                if(b < 3 && (b + a) % 2 == 0){
                    board[a][b] = 1;
                }
                else if(b > 4 && (b + a)%2 == 0){
                    board[a][b] = -1;
                }
                else{
                    board[a][b] = 0;
                }
            }
        }
    }

    public BoardPosition copy(){
        BoardPosition Clone = new BoardPosition();
        for(int a = 0; a < board.length; a++){
            for(int b = 0; b < board[0].length; b++){
                Clone.board[a][b] = board[a][b];
            }
        }
        return Clone;
    }

    /**
     * creates a BoardPosition from an existing one
     * @param BP
     * @param peiceToMove
     * @param newPlace
     */
    public BoardPosition(BoardPosition BP, int A, int B, int code){
        board = new int[8][8];
        for(int a = 0; a < board.length; a++){
            for(int b = 0; b < board[0].length; b++){
                board[a][b] = BP.board[a][b];  //copy it over
            }
        }
        int value = board[A][B];
        board[A][B] = 0;
        switch(code){
            case(0): A --;
                     B ++; break; //step right up
            case(1): A ++;
                     B ++; break; //step right down
            case(2): //jump right up
                     board[A-1][B+1] = 0;
                     A -= 2;
                     B += 2; break;
            case(3): //jump right down
                     board[A+1][B+1] = 0;
                     A += 2;
                     B += 2; break;
            case(4): A --;
                     B --; break; //step right up
            case(5): A ++;
                     B --; break; //step right down
            case(6): //jump right up
                     board[A-1][B-1] = 0;
                     A -= 2;
                     B -= 2;  break;
            case(7): //jump right down
                     board[A+1][B-1] = 0;
                     A += 2;
                     B -= 2;  break;
            default: break;
        }
        board[A][B] = value;
        if((B == 0 && value == -1) || (B == 7 && value == 1)){  //king it
            board[A][B] *= 2;
        }
    }

    /**
     * returns true if this is an ending position
     * @return
     */
    public boolean gameOver(boolean player1){
        return getMoves(player1).isEmpty();
    }

    /**
     * returns a list of peices which this player can legally move
     * @param player1
     * @return
     */
    public LinkedList <int[]> getMovablePeices(boolean player1){
        LinkedList <int[]> movablePieces = new LinkedList <int[]> ();

        //first we need to check for jump moves
        for(int a = 0; a < board.length; a++){
            for(int b = 0; b < board[0].length; b++){
                if(Math.signum(board[a][b]) == (player1 ? 1 : -1) && canJump(a, b)){  //if it is this player's peice
                    movablePieces.add(new int[]{a,b});  //add this peice to the list as a legal jumping peice
                }
            }
        }

        if(movablePieces.isEmpty()){  //if there are no pieces which can jump, we check for steping moves
            for(int a = 0; a < board.length; a++){
                for(int b = 0; b < board[0].length; b++){
                    if(Math.signum(board[a][b]) == (player1 ? 1 : -1) && canStep(a, b)){  //if it is this player's peice
                        movablePieces.add(new int[]{a,b});  //add this peice to the list as a legal jumping peice
                    }
                }
            }
        }
        return movablePieces;
    }

    /**
     * returns true if the peice at a,b can legally jump
     * @param a
     * @param b
     * @return
     */
    public boolean canJump(int a, int b){
        int peiceType = board[a][b];
        if((peiceType > 0 || peiceType == -2) && (jumpOK(a, b, a-1,b+1) || jumpOK(a, b, a+1,b+1))){  //check jumps in the positive direction
            return true;
        }
        if((peiceType < 0 || peiceType == 2) &&(jumpOK(a, b, a-1,b-1) || jumpOK(a, b, a+1,b-1))){  //check jumps in the negative direction
            return true;
        }
        return false;
    }

    /**
     * returns true if the peice at a,b can legally step
     * @param a
     * @param b
     * @return
     */
    public boolean canStep(int a, int b){
        int peiceType = board[a][b];
        if((peiceType > 0 || peiceType == -2) && (open(a-1,b+1) || open(a+1,b+1))){  //check steps in the positive direction
            return true;
        }
        if((peiceType < 0 || peiceType == 2) &&(open(a-1,b-1) || open(a+1,b-1))){  //check steps in the negative direction
            return true;
        }
        return false;
    }

    /**
     * returns the list of legal deviant board positions
     * @return
     */
    public LinkedList <BoardPosition> getMoves(boolean player1){
        LinkedList <BoardPosition> moves = new LinkedList <BoardPosition> ();

        for(int a = 0; a < board.length; a++){
            for(int b = 0; b < board[0].length; b++){
                if((player1 && board[a][b] > 0) || (!player1 && board[a][b] < 0)){
                    moves.addAll(getJumpMoves(a, b, board[a][b]));
                }
            }
        }

        if(moves.isEmpty()){  //only add step moves if there are no killing moves
            for(int a = 0; a < board.length; a++){
                for(int b = 0; b < board[0].length; b++){
                    int peiceType = board[a][b];
                    if(player1 && board[a][b] > 0){
                        if(open(a-1, b+1)){  //move right and up is open
                            moves.add(new BoardPosition(this, a, b, 0));
                        }
                        if(open(a+1, b+1)){  //move right and down is open
                            moves.add(new BoardPosition(this, a, b, 1));
                        }
                        if(board[a][b] == 2){
                            if(open(a-1, b-1)){  //move left and up is open
                                moves.add(new BoardPosition(this, a, b, 4));
                            }
                            if(open(a+1, b-1)){  //move leftt and down is open
                                moves.add(new BoardPosition(this, a, b, 5));
                            }
                        }
                    }
                    if(!player1 && board[a][b] < 0){
                        if(open(a-1, b-1)){  //move left and up is open
                            moves.add(new BoardPosition(this, a, b, 4));
                        }
                        if(open(a+1, b-1)){  //move leftt and down is open
                            moves.add(new BoardPosition(this, a, b, 5));
                        }
                        if(board[a][b] == -2){
                            if(open(a-1, b+1)){  //move right and up is open
                                moves.add(new BoardPosition(this, a, b, 0));
                            }
                            if(open(a+1, b+1)){  //move right and down is open
                                moves.add(new BoardPosition(this, a, b, 1));
                            }
                        }
                    }
                }
            }
        }

        return moves;
    }

    /**
     * returns the jump moves for the given piece
     * @param a
     * @param b
     * @return
     */
    public LinkedList <BoardPosition> getJumpMoves(int a, int b, int peiceType){
        LinkedList <BoardPosition> moves = new LinkedList <BoardPosition> ();
        if(peiceType > 0 || peiceType == -2){
            if(jumpOK(a, b, a-1,b+1)){
                BoardPosition newBP = new BoardPosition(this, a, b, 2);
                //this ensures that as many jumps as possible are made
                LinkedList <BoardPosition> derivativeJumps = newBP.getJumpMoves(a-2,b+2,peiceType);
                if(derivativeJumps.isEmpty()){
                    moves.add(newBP);
                }
                else{
                    moves.addAll(derivativeJumps);
                }
//                moves.add(newBP);
//                moves.addAll();  //add all the jump moves from this jump move
            }
            if(jumpOK(a, b, a+1,b+1)){
                BoardPosition newBP = new BoardPosition(this, a, b, 3);
                LinkedList <BoardPosition> derivativeJumps = newBP.getJumpMoves(a+2,b+2,peiceType);
                if(derivativeJumps.isEmpty()){
                    moves.add(newBP);
                }
                else{
                    moves.addAll(derivativeJumps);
                }
//                moves.add(newBP);
//                moves.addAll(newBP.getJumpMoves(a+2,b+2,peiceType));  //add all the jump moves from this jump move
            }
        }
        if(peiceType < 0 || peiceType == 2){
            if(jumpOK(a, b, a-1,b-1)){
                BoardPosition newBP = new BoardPosition(this, a, b, 6);
                LinkedList <BoardPosition> derivativeJumps = newBP.getJumpMoves(a-2,b-2,peiceType);
                if(derivativeJumps.isEmpty()){
                    moves.add(newBP);
                }
                else{
                    moves.addAll(derivativeJumps);
                }
//                moves.add(newBP);
//                moves.addAll(newBP.getJumpMoves(a-2,b-2,peiceType));  //add all the jump moves from this jump move
            }
            if(jumpOK(a, b, a+1,b-1)){
                BoardPosition newBP = new BoardPosition(this, a, b, 7);
                LinkedList <BoardPosition> derivativeJumps = newBP.getJumpMoves(a+2,b-2,peiceType);
                if(derivativeJumps.isEmpty()){
                    moves.add(newBP);
                }
                else{
                    moves.addAll(derivativeJumps);
                }
//                moves.add(newBP);
//                moves.addAll(newBP.getJumpMoves(a+2,b-2, peiceType));  //add all the jump moves from this jump move
            }
        }

        return moves;
    }

    /**
     * returns a list of coordinates the given peice can step to
     * NOTE: this does not check if the peice has a legal jump
     * @return
     */
    public LinkedList <int[]> getStepMoves(int a, int b){
        LinkedList <int[]> stepMoves = new LinkedList <int[]> ();
        int peiceType = board[a][b];
        if(peiceType > 0 || peiceType == -2){
            if(open(a-1,b+1)){
                stepMoves.add(new int[]{a-1,b+1});
            }
            if(open(a+1,b+1)){
                stepMoves.add(new int[]{a+1,b+1});
            }
        }
        if(peiceType < 0 || peiceType == 2){
            if(open(a-1,b-1)){
                stepMoves.add(new int[]{a-1,b-1});
            }
            if(open(a+1,b-1)){
                stepMoves.add(new int[]{a+1,b-1});
            }
        }
        return stepMoves;
    }

    /**
     * returns a list of coordinates the given peice can step to
     * NOTE: this does not check if the peice has a legal jump
     * @return
     */
    public LinkedList <int[]> getJumpMoves(int a, int b){
        LinkedList <int[]> jumpMoves = new LinkedList <int[]> ();
        int peiceType = board[a][b];
        if(peiceType > 0 || peiceType == -2){  //if it needs to move forward
            if(jumpOK(a, b, a-1,b+1)){
                jumpMoves.add(new int[]{a-2,b+2});
            }
            if(jumpOK(a, b, a+1,b+1)){
                jumpMoves.add(new int[]{a+2,b+2});
            }
        }
        if(peiceType < 0 || peiceType == 2){
            if(jumpOK(a, b, a-1,b-1)){
                jumpMoves.add(new int[]{a-2,b-2});
            }
            if(jumpOK(a, b, a+1,b-1)){
                jumpMoves.add(new int[]{a+2,b-2});
            }
        }
        return jumpMoves;
    }

    /**
     * returns if the given player has available jumps
     * @return
     */
    public boolean jumpsAvailable(boolean player1){
        for(int a = 0; a < board.length; a++){
            for(int b = 0; b < board[0].length; b++){
                if(((player1 && board[a][b] > 0) || (!player1 && board[a][b] < 0)) && (canJump(a,b))){
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * returns true if you can jump from a1, b1, over a2, b2
     * @param a
     * @param b
     * @return
     */
    public boolean jumpOK(int a1, int b1, int a2, int b2){
        return open(2*a2 - a1, 2*b2 - b1) && inBounds(a2, b2) && (Math.signum(board[a2][b2]) == -Math.signum(board[a1][b1]));
    }

    /**
     * true if the given coordinates are open
     * @param a
     * @param b
     * @return
     */
    public boolean open(int a, int b){
        return inBounds(a,b) && board[a][b] == 0;
    }

    public boolean inBounds(int a, int b){
        return a >= 0 && a < board.length && b >= 0 && b < board[0].length;
    }


    /**
     * what the score is for this board
     * @return
     */
    public double boardValue(){
//        int peiceDifference = 0;
//        for(int a = 0; a < board.length; a++){
//            for(int b = 0; b < board[0].length; b++){
//                peiceDifference += board[a][b];
//            }
//        }
//        return peiceDifference;

        double value = 0;
        int values[][] = {{4, 4, 4, 4, 4, 4, 4, 4},
                          {4, 3, 3, 3, 3, 3, 3, 3},
                          {4, 3, 2, 2, 2, 2, 2, 2},
                          {4, 3, 2, 1, 1, 2, 3, 4},
                          {4, 3, 2, 1, 1, 2, 3, 4},
                          {4, 3, 2, 2, 2, 2, 2, 2},
                          {4, 3, 3, 3, 3, 3, 3, 3},
                          {4, 4, 4, 4, 4, 4, 4, 4}};
        for(int a = 0; a < board.length; a++){
            for(int b = 0; b < board[0].length; b++){
                value += board[a][b] * values[a][b];
            }
        }
        return value;
    }

    @Override
    public String toString(){
        String s = "board: ";
        for(int a = 0; a < board.length; a++){
            s += "\n";
            for(int b = 0; b < board[0].length; b++){
                switch(board[a][b]){
                    case(-2): s += 'B'; break;
                    case(-1): s += 'b'; break;
                    case(0): s += '_'; break;
                    case(1): s += 'r'; break;
                    case(2): s += 'R'; break;
                    default: break;
                }
                s += " ";
            }
        }
        return s;
    }
}
