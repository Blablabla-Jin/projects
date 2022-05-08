/**
 * @file: gameController.java
 * @Author: Boming Jin - jinb5
 * @Date: April 9 2021
 * @Description: a module for controll the game
 */



package src;

import java.util.*;

public class gameController {

    // Define state variables
    private BoardT board;
    private userInterface view;
    private static gameController controller = null;
    
    // Define environment variable
    private Scanner keyboard = new Scanner(System.in);
    private boolean gameEnd = false;
    private boolean gameRestart = true;

    /**
     * @brief constructor
     * @details generates a controller with BoardT
     */
    public gameController(BoardT b, userInterface view)
    {
        this.board = b;
        this.view = view;
    }

    /**
     * @brief public static method for obtaining a single instance
     * @return the single GameController object
     */
    public static gameController getInstance(BoardT b, userInterface view) 
    { 
        if (controller == null) 
            controller = new gameController(b, view); 
  
        return controller; 
    } 

    /**
     * @brief initialize the game
     */
    public void initializeGame(){
        this.board = new BoardT();
    }

    /**
     * @brief takes the input from the user through keyboard
     * @return the input
     */
    public String readInput(){
        String input = " ";
        input = keyboard.nextLine();
        input = input.toLowerCase();
        try{
            if(!input.equals("w") && !input.equals("a") && !input.equals("s") && !input.equals("d")
               && !input.equals("r") && !input.equals("e"))
                throw new IllegalArgumentException();
        }
        catch (IllegalArgumentException e) {
            System.out.println("Invalid Input");
            
        }
        return input;
    }

    /**
     * @brief check the condition of the game
     * @details local function for check if the game is over true for fail
     */
    private boolean gameOver()
    {
        if (this.board.isFull())
        {
            //check if there exist adjacent cells are equal, true for equal, false for none
            ArrayList<Boolean> columnCheck = new ArrayList<Boolean>();
            ArrayList<Boolean> rowCheck = new ArrayList<Boolean>();

            for (int x = 0; x < this.board.getBoard().size(); x++)
            {
                for (int y = 0; y < this.board.getBoard().size() - 1; y++)
                {
                    if (this.board.getBoard().get(x).get(y).getNumber() == this.board.getBoard().get(x).get(y + 1).getNumber())
                    {
                        //if exits same number add true in to rowCheck
                        rowCheck.add(true);
                        break;
                    }
                    rowCheck.add(false);
                }
            }

            for (int j = 0; j < this.board.getBoard().size(); j++)
            {
                for (int i = 0; i < this.board.getBoard().size() - 1; i++)
                {
                    if (this.board.getBoard().get(i).get(j).getNumber() == this.board.getBoard().get(i + 1).get(j).getNumber())
                    {
                        columnCheck.add(true);
                        break;
                    }
                    columnCheck.add(false);
                }
            }


            if (columnCheck.contains(true) || rowCheck.contains(true))
            {
                this.gameEnd = false;
            }
            else
            {
                this.gameEnd = true;
            }
        }

        return this.gameEnd;
    }

    /**
     * @brief updates the view module to display a welcome message
     */
    public void welcomeMessage(){
        view.printWelcomeMessage();
    }

    /**
     * @brief updates the view module to display a message for users
     */
    public void gameMessage(){
        view.printGameMessage();
    }

    /**
     * @brief updates the view module to display the board
     */
    public void displayBoard(){
        view.printBoard(this.board);
    }

    /**
     * @brief updates the view module to display the game objective
     */
    public void displayInformation(){
        view.printInformation("Your Score: " + String.valueOf(this.board.getScore()));
    }

    /**
     * @brief updates the view module to display a ending message
     */
    public void displayEnding(){
        view.printEndingMessage();
    }

    /**
     * @brief run the game
     */
    public void runGame()
    {
        String input = "";
        welcomeMessage();
        do
        {
            gameMessage();
            initializeGame();

            while(!this.gameEnd)
            {

                displayInformation();
                displayBoard();
                input = readInput();
                if (input.equals("w"))
                {
                    this.board.moveUp();
                }
                else if (input.equals("a")){
                    this.board.moveLeft();
                }
                else if (input.equals("s")){
                    this.board.moveDown();
                }
                else if (input.equals("d")){
                    this.board.moveRight();
                }
                else if (input.equals("e")){
                    this.gameRestart = false;
                    break;
                }

                this.gameEnd = gameOver();
                
                if (this.gameEnd)
                {
                    //For display final look of the board
                    displayInformation();
                    displayBoard();
                    
                    System.out.println("No more possible movings! Wants to restart the game?");
                    System.out.println("Press 'r' for resatart. Any other listed buttons to quit the game!");
                    input = readInput();
                    if (input.equals("r"))
                    {
                        this.gameRestart = true;
                        this.gameEnd = false;
                        break;
                    }
                    else
                    {
                        this.gameRestart = false;
                        break;
                    }
                }
            }
        }while (this.gameRestart);
        displayEnding();
        System.exit(0);
    }

}
