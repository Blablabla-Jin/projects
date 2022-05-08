/**
 * @file: BoardT.java
 * @Author: Boming Jin - jinb5
 * @Date: April 9 2021
 * @Description: a module for storing the stete and the status of the game
 */

package src;

import java.util.*;


public class BoardT 
{
    // Define state variables
    private ArrayList<ArrayList<StatusT>> board;
    private boolean full = false;
    private int score;

    //Exported Constants
    private final static int size = 4;

    /**
     * @brief constructor
     * @details generates a board with 2 random places which are number of 2 or 4
     */
    public BoardT() 
    {
        // give out the default board at the begining
        this.score = 0;
        this.board = new ArrayList<ArrayList<StatusT>>();

        for (int i = 0; i < size; i++) {
            this.board.add(new ArrayList<StatusT>(Arrays.asList(new StatusT(BoardType.empty, 0), new StatusT(BoardType.empty, 0), new StatusT(BoardType.empty, 0), new StatusT(BoardType.empty, 0))));
        }

        spawnNum();
        spawnNum();

    }

    /**
     * @brief constructor
     * @details generates a board with 2 random places which are number of 2 or 4
     * @param b is the 2d arraylist that storing the status of each cell in the board
     */
    public BoardT(ArrayList<ArrayList<StatusT>> b) 
    {
        // give out the default board at the begining
        this.score = 0;
        this.board = b;
        

        spawnNum();
        spawnNum();

    }

    /**
     * @brief set board information
     * @param s StatusT for construct BoardT
     * @param r number representing the which row should be set
     * @param c number representing the which column should be set
     */
    public void setBoard(StatusT s, int r, int c)
    {
        this.board.get(r).set(c, s);
    }

    /**
     * @brief set board information
     * @param s integer that represent the score the game
     */
    public void setScore(int s)
    {
        this.score = s;
    }


    /**
     * @brief getter
     * @returns return the arraylist of the board
     */
    public ArrayList<ArrayList<StatusT>> getBoard()
    {
        return this.board;
    }

    /**
     * @brief getter
     * @returns return the score of the game
     */
    public int getScore()
    {
        return this.score;
    }


    /**
     * @brief getter
     * @returns return true if the board is full of numbers
     */
    public boolean isFull()
    {
        for (int x = 0; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                if (this.board.get(x).get(y).getNumber() == 0)
                {
                    this.full = false;
                    break;
                }
                else
                {
                    this.full = true;
                }
            }
            if (!this.full)
            {
                break;
            }
        }
        return this.full;
    }

    /**
     * @brief Spawn 2 or 4 in random places of the board
     */
    private void spawnNum()
    {
        boolean drawn = false;
        boolean hasZero = false;

        // Check if board contains 0, if it contains 0 then jump out of the loop and spwan a new number
        for (int x = 0; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                if (this.board.get(x).get(y).getNumber() == 0)
                {
                    hasZero = true;
                    break;
                }
                else
                {
                    continue;
                }
            }
            if (hasZero)
            {
                break;
            }
        }
        if (!hasZero)
        {
            drawn = true;
        }

        // Keep find empty(has number of 0) to spawn a new number
        while(!drawn)
        {
            int randRow = (int) (Math.random() * 4);
            int randCol = (int) (Math.random() * 4);
            double two_fours = Math.random();

            if (this.board.get(randRow).get(randCol).getStatus() == BoardType.empty)
            {
                if (two_fours < 0.2) {
                    this.board.get(randRow).set(randCol, new StatusT(BoardType.hasnumber, 4));
                    drawn = true;
                }
                else
                {
                    this.board.get(randRow).set(randCol, new StatusT(BoardType.hasnumber, 2));
                    drawn = true;
                }
            }
            
        }

        
    }

    /**
     * @brief moving up
     */
    public void moveUp() {
        for (int x = 1; x < this.board.size(); x++) {
            for (int y = 0; y < this.board.size(); y++) {
                move("w", x, y, true);
            }
        }

        for (int x = 1; x < this.board.size(); x++) {
            for (int y = 0; y < this.board.size(); y++) {
                move("w", x, y, false );
            }
        }
        spawnNum();


    }

    /**
     * @brief moving left
     */
    public void moveLeft() {
        for (int y = 1; y < this.board.size(); y++) {
            for (int x = 0; x < this.board.size(); x++) {
                move("a", x, y, true);
            }
        }

        for (int y = 1; y < this.board.size(); y++) {
            for (int x = 0; x < this.board.size(); x++) {
                move("a", x, y, false);
            }
        }
        spawnNum();

    }

    /**
     * @brief moving down
     */
    public void moveDown() {
        for (int x = this.board.size() - 2; x >= 0; x--) {
            for (int y = 0; y < this.board.size(); y++) {
                move("s", x, y, true);
            }
        }

        for (int x = 1; x < this.board.size(); x++) {
            for (int y = 0; y < this.board.size(); y++) {
                move("s", x, y, false );
            }
        }
        spawnNum();

    }

    /**
     * @brief moving right
     */
    public void moveRight() {
        for (int y = this.board.size() - 2; y >= 0; y--) {
            for (int x = 0; x < this.board.size(); x++) {
                move("d", x, y, true);
            }
        }

        for (int y = this.board.size() - 2; y >= 0; y--) {
            for (int x = 0; x < this.board.size(); x++) {
                move("d", x, y, false);
            }
        }
        spawnNum();

    }



    /**
     * @brief move whole cells in a row/column
     * @details local function for moving a row/column of the board
     */
    private void move(String s, int x, int y, boolean moved)
    {
        if (s.equals("w"))
        {
            for (; x > 0; x--) {
                swap(this.board.get(x).get(y), this.board.get(x - 1).get(y), moved);
            }
        }
        else if (s.equals("a"))
        {
            for (; y > 0; y--) {
                swap(this.board.get(x).get(y), this.board.get(x).get(y - 1), moved);
            }
        }
        else if (s.equals("s"))
        {
            for (; x < this.board.size() - 1; x++) {
                swap(this.board.get(x).get(y), this.board.get(x + 1).get(y), moved);
            }
        }
        else if (s.equals("d"))
        {
            for (; y < this.board.size() - 1; y++) {
                swap(this.board.get(x).get(y), this.board.get(x).get(y + 1), moved);
            }
        }
    }

    /**
     * @brief swap cells
     * @details local function for swqp two adjacent cell in the same row/column
     */
    private void swap(StatusT current, StatusT nextPos, boolean moved)
    {
        if (moved)
        {
            
            if(current.getNumber() != 0 && nextPos.getNumber() == 0)
            {
                nextPos.setNumber(current.getNumber());
                nextPos.setStatus(BoardType.hasnumber);
                current.setNumber(0);
                current.setStatus(BoardType.empty);
                nextPos.setMoveCondition(false);
            }

            else if(current.getNumber() != 0 && nextPos.getNumber() != 0 && !current.getMoveCondition() && !nextPos.getMoveCondition())
            {
                if (current.getNumber() == nextPos.getNumber())
                {
                    nextPos.setNumber(2 * nextPos.getNumber());
                    current.setNumber(0);
                    current.setStatus(BoardType.empty);
                    nextPos.setMoveCondition(true);
                    current.setMoveCondition(false);
                    this.score += nextPos.getNumber();
                }
            }
        }
        else
        {   
            current.setMoveCondition(false);
            nextPos.setMoveCondition(false);
        }
        
    }

}
