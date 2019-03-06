package checkers;

import board.*;
import checkers.*;
import java.awt.event.*;
import java.util.LinkedList;

/**
 *
 * @author tim
 */
public class RealPlayer implements Player{

    public BoardPosition board;  //the futuristic structure
    public boolean player1;  //if this is player 1

    public int click[];  //the grid coordinates of the last click
    public int drag;  //the direction of the drag, by quadrant.  I.E. 1 is up-right, 2 is up-left, etc.
    public boolean clicked;

    public RealPlayer(BoardPosition BP, boolean player1){
        board = BP;
        this.player1 = player1;
        clicked = false;
    }

    @Override
    public BoardPosition getMove(){
        int startX;
        int startY;
        while(true){
            //we need them to select a peice and drag it to where it goes
            getClickAndDrag();

            if(board.inBounds(click[0], click[1])  //if it is in bounds
                    && Math.signum(board.board[click[0]][click[1]]) == (player1 ? 1 : -1)){  //if it is owned by this player

                BoardPosition temp = board.copy();
                //now we need to see what the possible moves are
                if(temp.jumpsAvailable(player1) && temp.canJump(click[0], click[1])){  //if this peice can jump
//                    System.out.println("Can JUMP");
                    LinkedList <int[]> possibleMoves = temp.getJumpMoves(click[0], click[1]); //get the possible jump moves
                    if(possibleMoves.size() == 1){//if only one is possible
//                        System.out.println("One Possible Move");
                        int[] move = possibleMoves.get(0);  //the only possible move
                        int a = move[0] - click[0];  //the horizontal shift
                        int b = move[1] - click[1];  //the vertical shift
//                        System.out.println("a: " + a + "  b: " + b);
                        if(a == -2 && b == 2){
                            temp = new BoardPosition(temp, click[0], click[1], 2);//step and return modified temp
                        }
                        else if(a == 2 && b == 2){
                            temp = new BoardPosition(temp, click[0], click[1], 3);
                        }
                        else if(a == -2 && b == -2){
                            temp = new BoardPosition(temp, click[0], click[1], 6);
                        }
                        else if(a == 2 && b == -2){
                            temp = new BoardPosition(temp, click[0], click[1], 7);
                        }
                        int loc[] = {move[0], move[1]};  //where the active peice now is
                        while(temp.canJump(loc[0],loc[1])){  //as long as this peice can jump
                            possibleMoves = temp.getJumpMoves(loc[0], loc[1]); //get the possible jump moves
                            if(possibleMoves.size() == 1){ //if only one possible move
                                move = possibleMoves.get(0);  //the only possible move
                                a = move[0] - loc[0];  //the horizontal shift
                                b = move[1] - loc[1];  //the vertical shift
                                if(a == -2 && b == 2){
                                    temp = new BoardPosition(temp, loc[0], loc[1], 2);//step and return modified temp
                                }
                                else if(a == 2 && b == 2){
                                    temp = new BoardPosition(temp, loc[0], loc[1], 3);
                                }
                                else if(a == -2 && b == -2){
                                    temp = new BoardPosition(temp, loc[0], loc[1], 6);
                                }
                                else if(a == 2 && b == -2){
                                    temp = new BoardPosition(temp, loc[0], loc[1], 7);
                                }
                                loc[0] = move[0];
                                loc[1] = move[1];  //where the active peice now is
                            }
                            else{  //we have a choice to make in the jump direction
                                getClickAndDrag();
                                if(click[0] == loc[0] && click[1] == loc[1] //if the click was on the correct peice
                                    && drag != 0){   //and the drag was legal
                                    int pos[] = {click[0], click[1]};
                                    switch(drag){
                                        case(1): pos[0] +=2; pos[1] +=2; break;
                                        case(2): pos[0] +=2; pos[1] -=2; break;
                                        case(3): pos[0] -=2; pos[1] -=2; break;
                                        case(4): pos[0] -=2; pos[1] +=2; break;
                                        default: break;
                                    }
                                    for(int tempMove[]: possibleMoves){
                                        if(tempMove[0] == pos[0] && tempMove[1] == pos[1]){  //if the dragged direction matches up with a possible move
                                            a = tempMove[0] - loc[0];  //the horizontal shift
                                            b = tempMove[1] - loc[1];  //the vertical shift
                                            if(a == -2 && b == 2){
                                                temp = new BoardPosition(temp, loc[0], loc[1], 2);//step and return modified temp
                                            }
                                            else if(a == 2 && b == 2){
                                                temp = new BoardPosition(temp, loc[0], loc[1], 3);
                                            }
                                            else if(a == -2 && b == -2){
                                                temp = new BoardPosition(temp, loc[0], loc[1], 6);
                                            }
                                            else if(a == 2 && b == -2){
                                                temp = new BoardPosition(temp, loc[0], loc[1], 7);
                                            }
                                            loc[0] = move[0];
                                            loc[1] = move[1];  //where the active peice now is
                                        }
                                    }
                                }
                            }
                        }
                        return temp;
                    }

                    else{
                        int pos[] = {click[0], click[1]};
                        switch(drag){
                            case(1): pos[0] +=2; pos[1] +=2; break;
                            case(2): pos[0] +=2; pos[1] -=2; break;
                            case(3): pos[0] -=2; pos[1] -=2; break;
                            case(4): pos[0] -=2; pos[1] +=2; break;
                            default: break;
                        }
                        for(int[] move: possibleMoves){
                            if(move[0] == pos[0] && move[1] == pos[1]){  //if the dragged direction matches up with a possible move
                                int a = move[0] - click[0];  //the horizontal shift
                                int b = move[1] - click[1];  //the vertical shift
                                if(a == -2 && b == 2){
                                    temp = new BoardPosition(temp, click[0], click[1], 2);//step and return modified temp
                                }
                                else if(a == 2 && b == 2){
                                    temp = new BoardPosition(temp, click[0], click[1], 3);
                                }
                                else if(a == -2 && b == -2){
                                    temp = new BoardPosition(temp, click[0], click[1], 6);
                                }
                                else if(a == 2 && b == -2){
                                    temp = new BoardPosition(temp, click[0], click[1], 7);
                                }
                                int loc[] = {move[0], move[1]};  //where the active peice now is
                                while(temp.canJump(loc[0],loc[1])){  //as long as this peice can jump
                                    possibleMoves = temp.getJumpMoves(click[0], click[1]); //get the possible jump moves
                                    if(possibleMoves.size() == 1){ //if only one possible move
                                        move = possibleMoves.get(0);  //the only possible move
                                        a = move[0] - click[0];  //the horizontal shift
                                        b = move[1] - click[1];  //the vertical shift
                                        if(a == -2 && b == 2){
                                            temp = new BoardPosition(temp, loc[0], loc[1], 2);//step and return modified temp
                                        }
                                        else if(a == 2 && b == 2){
                                            temp = new BoardPosition(temp, loc[0], loc[1], 3);
                                        }
                                        else if(a == -2 && b == -2){
                                            temp = new BoardPosition(temp, loc[0], loc[1], 6);
                                        }
                                        else if(a == 2 && b == -2){
                                            temp = new BoardPosition(temp, loc[0], loc[1], 7);
                                        }
                                        loc[0] = move[0];
                                        loc[1] = move[1];  //where the active peice now is
                                    }
                                    else{  //we have a choice to make in the jump direction
                                        getClickAndDrag();
                                        if(click[0] == loc[0] && click[1] == loc[1] //if the click was on the correct peice
                                            && drag != 0){   //and the drag was legal
                                            pos[0] = click[0];
                                            pos[1] = click[1];
                                            switch(drag){
                                                case(1): pos[0] +=2; pos[1] +=2; break;
                                                case(2): pos[0] +=2; pos[1] -=2; break;
                                                case(3): pos[0] -=2; pos[1] -=2; break;
                                                case(4): pos[0] -=2; pos[1] +=2; break;
                                                default: break;
                                            }
                                            for(int tempMove[]: possibleMoves){
                                                if(tempMove[0] == pos[0] && tempMove[1] == pos[1]){  //if the dragged direction matches up with a possible move
                                                    a = tempMove[0] - loc[0];  //the horizontal shift
                                                    b = tempMove[1] - loc[1];  //the vertical shift
                                                    if(a == -2 && b == 2){
                                                        temp = new BoardPosition(temp, loc[0], loc[1], 2);//step and return modified temp
                                                    }
                                                    else if(a == 2 && b == 2){
                                                        temp = new BoardPosition(temp, loc[0], loc[1], 3);
                                                    }
                                                    else if(a == -2 && b == -2){
                                                        temp = new BoardPosition(temp, loc[0], loc[1], 6);
                                                    }
                                                    else if(a == 2 && b == -2){
                                                        temp = new BoardPosition(temp, loc[0], loc[1], 7);
                                                    }
                                                    loc[0] = move[0];
                                                    loc[1] = move[1];  //where the active peice now is
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        return temp;
                    }
                }
                else if(!temp.jumpsAvailable(player1) && board.canStep(click[0], click[1])){  //if it can step one block forward and there are no available jump moves
                    LinkedList <int[]> possibleMoves = board.getStepMoves(click[0], click[1]);  //get the possible step moves
                    if(possibleMoves.size() == 1){//if only one is possible
                        int[] move = possibleMoves.get(0);  //the only possible move
                        int a = move[0] - click[0];  //the horizontal shift
                        int b = move[1] - click[1];  //the vertical shift
                        if(a == -1 && b == 1){
                            return new BoardPosition(temp, click[0], click[1], 0);//step and return modified temp
                        }
                        else if(a == 1 && b == 1){
                            return new BoardPosition(temp, click[0], click[1], 1);
                        }
                        else if(a == -1 && b == -1){
                            return new BoardPosition(temp, click[0], click[1], 4);
                        }
                        else if(a == 1 && b == -1){
                            return new BoardPosition(temp, click[0], click[1], 5);
                        }
                    }
                    else{
                        int pos[] = {click[0], click[1]};
                        switch(drag){
                            case(1): pos[0] ++; pos[1] ++; break;
                            case(2): pos[0] ++; pos[1] --; break;
                            case(3): pos[0] --; pos[1] --; break;
                            case(4): pos[0] --; pos[1] ++; break;
                            default: break;
                        }
                        for(int[] move: possibleMoves){
                            if(move[0] == pos[0] && move[1] == pos[1]){  //if the dragged direction matches up with a possible move
                                int a = move[0] - click[0];  //the horizontal shift
                                int b = move[1] - click[1];  //the vertical shift
                                if(a == -1 && b == 1){
                                    return new BoardPosition(temp, click[0], click[1], 0);//step and return modified temp
                                }
                                else if(a == 1 && b == 1){
                                    return new BoardPosition(temp, click[0], click[1], 1);
                                }
                                else if(a == -1 && b == -1){
                                    return new BoardPosition(temp, click[0], click[1], 4);
                                }
                                else if(a == 1 && b == -1){
                                    return new BoardPosition(temp, click[0], click[1], 5);
                                }
                            }
                        }
                    }
                }   
            }
        }
    }

    @Override
    public void update(BoardPosition BP, boolean player1){
       board = BP;
    }

    /**
     * waits until the player clicks
     */
    public void getClickAndDrag(){
        clicked = false;  //set it to false to wait for click...
        while(!clicked){
            try{Thread.sleep(100);}catch(Exception e){}
        }
    }

    public void onMousePressed(MouseEvent e){
        if(!clicked){  //only activate if it is waiting for a click selection
            click = new int[]{(e.getX()-105)/50, (e.getY()-225)/50};  //the coordinates of the clicking
        }
    }
    public void onMouseReleased(MouseEvent e){
        if(!clicked){  //only activate if it is waiting for a click selection
            int dragVector[] = {(e.getX()-105)/50 - click[0], (e.getY()-225)/50 - click[1]};
            if(dragVector[0] == 0 || dragVector[1] == 0){
                drag = 0; //invalid entry, must be a diagonal
            }
            else if(dragVector[0] > 0 && dragVector[1] > 0){  //set drag to the appropriate quadrant
                drag = 1;
            }
            else if(dragVector[0] > 0){
                drag = 2;
            }
            else if(dragVector[1] > 0){
                drag = 4;
            }
            else{
                drag = 3;
            }
            clicked = true;
        }
    }
}
