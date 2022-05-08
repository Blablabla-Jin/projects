/**
 * @file: userInterface.java
 * @Author: Boming Jin - jinb5
 * @Date: April 9 2021
 * @Description: a module of display userinterface for users
 */

package src;

public class userInterface {
    
    private static userInterface view = null;

    /** 
     * @brief constructor
     */
    private userInterface(){}

    /**
     * @brief public static method for obtaining a single instance
     * @return an UserInterface object
     */
    public static userInterface getInstance(){
        if (view == null)
            return view = new userInterface();
        return view;
    }

    /**
     * @brief display a welcome message
     */
    public void printWelcomeMessage(){
        System.out.println("-------------------------------------------------");
        System.out.println("                 Welcome to 2048                 ");
        System.out.println("-------------------------------------------------");
    }

    /**
     * @brief display a message to telling user about the game
     */
    public void printGameMessage(){
        System.out.println("                     New game                    ");
        System.out.println("                 -----------------               ");
        System.out.println("");
        System.out.println("You can play this game now!");
        System.out.println("Press 'w' 'a' 's' 'd' for moving!");
        System.out.println("Press 'r' for restart the game!");
        System.out.println("Press 'e' for exit the game!");
    }

    /**
     * @brief display the game objective
     * @param message - the game scores
     */
    public void printInformation(String message){
        System.out.println(message);
    }

    /**
     * @brief Display the board on the screen
     * @details print a 4 x 4 game board for users
     * @param board - the game board
     */
    public void printBoard(BoardT board)
    {
        for (int x = 0; x < 4; x++){
            for (int y = 0; y < 4; y++){
               System.out.print(board.getBoard().get(x).get(y).getNumber() + "   ");
            }
            System.out.println(); 
        }

    }

    /**
     * @brief display an ending message after user choose to exit the game
     */
    public void printEndingMessage(){
        System.out.println("-------------------------------------------------");
        System.out.println("             Thanks for playing !!!              ");
        System.out.println("-------------------------------------------------");
    }

}
