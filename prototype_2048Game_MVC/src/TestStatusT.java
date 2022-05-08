/**
 * @file: TestStatusT.java
 * @Author: Boming Jin - jinb5
 * @Date: April 9, 2021
 * @Description: Tests the access routines of StatusT.java
 */

package src;

import org.junit.*;

import jdk.jfr.Timestamp;
import src.StatusT;

import static org.junit.Assert.*;
import java.util.*;

public class TestStatusT
{
    private StatusT status;

    @Before
    public void setUp()
    {
        status = new StatusT(BoardType.empty, 0);
    }

    @After
    public void tearDown()
    {
        status = null;
    }

    @Test
    public void testGetStatus()
    {
        assertTrue(status.getStatus() == BoardType.empty);
    }

    @Test
    public void testGetNumber()
    {
        assertTrue(status.getNumber() == 0);
    }

    @Test
    public void testGetMoveCondition()
    {
        assertTrue(status.getMoveCondition() == false);
    }

    @Test
    public void testSetStatus()
    {
        status.setStatus(BoardType.hasnumber);
        assertTrue(status.getStatus() == BoardType.hasnumber);

    }

    @Test
    public void testSetNumber()
    {
        status.setNumber(520);
        assertTrue(status.getNumber() == 520);
    }

    @Test
    public void testSetMoveCondition()
    {
        
        status.setMoveCondition(true);
        assertTrue(status.getMoveCondition() == true);
    }

}