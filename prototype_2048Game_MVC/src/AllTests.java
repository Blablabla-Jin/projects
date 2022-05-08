/**
 * @file: AllTests.java
 * @Author: Boming Jin - jinb5
 * @Date: April 9 2021
 * @Description: AllTests
 */

package src;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;

@RunWith(Suite.class)
@Suite.SuiteClasses({
   TestBoardT.class,	
   TestStatusT.class,
})

public class AllTests
{
}
