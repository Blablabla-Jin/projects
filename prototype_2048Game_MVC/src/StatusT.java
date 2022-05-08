/**
 * @file: StatusT.java
 * @Author: Boming Jin - jinb5
 * @Date: April 9 2021
 * @Description: a module for storing the status of each cell of the board
 */

package src;

public class StatusT 
{
    // Define state variables
    private BoardType status;
    private int num;
    private boolean moved = false;

    /**
     * @brief constructor
     * @details generates a status for each cell of the board
     */
    public StatusT(BoardType t, Integer i)
    {
        this.status = t;
        this.num = i;
    }

    /**
     * @brief set status
     */
    public void setStatus(BoardType t)
    {
        this.status = t;
    }

    /**
     * @brief set number
     */
    public void setNumber(Integer i)
    {
        this.num = i;
    }

    /**
     * @brief set the moving condition of the cell true for moved(added once in one moving), false for not
     */
    public void setMoveCondition(Boolean b)
    {
        this.moved = b;
    }

    /**
     * @brief getter
     * @returns return the status of the cell
     */
    public BoardType getStatus()
    {
        return this.status;
    }

    /**
     * @brief getter
     * @returns return the value of the cell
     */
    public Integer getNumber()
    {
        return this.num;
    }

    /**
     * @brief getter
     * @returns return the boolean value to judge if this cell been moved true for moved(added once in one moving), false for not
     */
    public boolean getMoveCondition()
    {
        return this.moved;
    }
}
