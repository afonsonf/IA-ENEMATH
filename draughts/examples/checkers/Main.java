package checkers;

import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import java.util.*;

/**
 *
 * @author tim
 */
public class Main extends JPanel implements KeyListener, FocusListener{

    public long sleepTime;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        System.out.println("Welcome to Checkers");

        LinkedList <String> records = new LinkedList <String> ();
        Random rand = new Random();

        GameTreeNode RED = new GameTreeNode(new BoardPosition());  //the player (incidentally, both players)
        for(int a = 0; a < 8; a ++){
            RED.sprout(true);
        }

        boolean player1 = true;
        while(!RED.BP.gameOver(player1) && !records.contains(RED.BP.toString())){
            System.out.println(RED.BP);
            records.add(RED.BP.toString());

            RED = RED.getMove(player1);  //tell red to become the next node down in its minimax list
            player1 = !player1;
            RED.sprout(player1);
        }
        System.out.println(RED.BP);
        System.out.println("GAME OVER");
        

//        int height = 600;
//        int width = 900;
//
//        JFrame myJFrame = new JFrame("Checkers");
//        Main myMain = new Main(10, width, height);
//        myJFrame.setSize(width,height);
//        myJFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//        myJFrame.add(myMain);  //add the viewer (itself) into the frame
//        myJFrame.setVisible(true);
//
//        myJFrame.addFocusListener(myMain);
//        myJFrame.addKeyListener(myMain);
//        myJFrame.requestFocus();  //get focus
    }

    public Main(long sleepTime, int width, int height){
        this.sleepTime = sleepTime;
    }

    @Override
    public void paintComponent(Graphics g){
        setBackground(Color.WHITE);
        super.paintComponent(g);

        if(sleepTime >= 0){
            double screenDimensions[] = {getWidth(), getHeight()};
            try{
//               myPopulation.draw(g);
            }catch(Exception e){System.out.println("Exception: " + e);}
            g.setColor(Color.BLACK);
            g.drawString("" + sleepTime, 0, 10);
        }

        repaint();

        try{Thread.sleep(sleepTime);}catch(Exception e){}
    }

    public void keyTyped(KeyEvent e){}
    public void keyPressed(KeyEvent e){
        //they pressed a key
        if(e.getKeyCode() == KeyEvent.VK_W){  //pressed the W key
            sleepTime ++;  //increment the sleep time
        }
        else if(e.getKeyCode() == KeyEvent.VK_S){  //pressed the S key
            sleepTime --;
        }
    }
    public void keyReleased(KeyEvent e){}
    public void focusLost(FocusEvent e){}
    public void focusGained(FocusEvent e){}
}
