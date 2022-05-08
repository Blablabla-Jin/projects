/**
 * @file: Demo.java
 * @Author: Boming Jin - jinb5
 * @Date: April 9 2021
 * @Description: Runs the game
 */

package src;

import java.util.*;


public class Demo
 {
    public static void main(String[] args) {
        
        BoardT board = new BoardT();
        userInterface view = userInterface.getInstance();
        gameController game = gameController.getInstance(board, view);
        game.runGame();
        


    }
}
