/**
 * @file: TestBoardT.java
 * @Author: Boming Jin - jinb5
 * @Date: April 9, 2021
 * @Description: Tests the access routines of BoardT.java
 */

package src;

import org.junit.*;

import jdk.jfr.Timestamp;
import src.BoardT;

import static org.junit.Assert.*;
import java.util.*;

public class TestBoardT
{
    private BoardT board;
    private StatusT status;
    private ArrayList<ArrayList<StatusT>> b;

    @Before
    public void setUp()
    {

        b = new ArrayList<ArrayList<StatusT>>();
        b.add(new ArrayList<StatusT>(Arrays.asList(new StatusT(BoardType.empty, 0), new StatusT(BoardType.empty, 0), 
                                                   new StatusT(BoardType.empty, 0), new StatusT(BoardType.empty, 0))));
        b.add(new ArrayList<StatusT>(Arrays.asList(new StatusT(BoardType.empty, 0), new StatusT(BoardType.empty, 0), 
                                                   new StatusT(BoardType.empty, 0), new StatusT(BoardType.empty, 0))));
        b.add(new ArrayList<StatusT>(Arrays.asList(new StatusT(BoardType.empty, 0), new StatusT(BoardType.empty, 0), 
                                                   new StatusT(BoardType.empty, 0), new StatusT(BoardType.empty, 0))));
        b.add(new ArrayList<StatusT>(Arrays.asList(new StatusT(BoardType.empty, 0), new StatusT(BoardType.empty, 0), 
                                                   new StatusT(BoardType.empty, 0), new StatusT(BoardType.empty, 0))));
        board = new BoardT(b);
        status = new StatusT(BoardType.hasnumber, 100);
    }

    @After
    public void tearDown()
    {
        board = null;
        status = null;
    }

    @Test
    public void testSetBoard()
    {
        board.setBoard(status, 0, 0);
        assertTrue(board.getBoard().get(0).get(0) == status);
    }

    @Test
    public void testSetScore()
    {
        board.setScore(360);
        assertTrue(board.getScore() == 360);
    }

    @Test
    public void testGetScore()
    {
        assertTrue(board.getScore() == 0);
    }

    @Test
    public void testGetBoard()
    {
        assertTrue(board.getBoard() == b);

    }

    @Test
    public void testIsFull()
    {
        assertTrue(board.isFull() == false);
    }

    @Test
    public void testMoveUp()
    {
    	for (int x = 0; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                board.getBoard().get(x).get(y).setNumber(0);
            }
        }
    	board.getBoard().get(2).get(0).setNumber(66);
    	board.moveUp();
        assertTrue(board.getBoard().get(0).get(0).getNumber() == 66);
    }

    @Test
    public void MoveDown()
    {
    	for (int x = 0; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                board.getBoard().get(x).get(y).setNumber(0);
            }
        }
    	board.getBoard().get(2).get(0).setNumber(88);
    	board.moveDown();
        assertTrue(board.getBoard().get(3).get(0).getNumber() == 88);
    }

    @Test
    public void MoveLeft()
    {
    	for (int x = 0; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                board.getBoard().get(x).get(y).setNumber(0);
            }
        }
    	board.getBoard().get(2).get(3).setNumber(20);
    	board.moveLeft();
        assertTrue(board.getBoard().get(2).get(0).getNumber() == 20);
    }

    @Test
    public void MoveRight()
    {
    	for (int x = 0; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                board.getBoard().get(x).get(y).setNumber(0);
            }
        }
    	board.getBoard().get(2).get(0).setNumber(21);
    	board.moveRight();
        assertTrue(board.getBoard().get(2).get(3).getNumber() == 21);
    }

}