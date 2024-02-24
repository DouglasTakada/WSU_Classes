#include "testQueue.h"


/**ATTRIBUTES
 *  1. There was a lack of comments in places where they were doing complex logic (Lack readability)
 * 
 *  2. The File structure was very poor because it was very unorognized. If anyone were to try to find something in this program they would have to go through the entire main.cpp file. (Inefficient/ Lack readabiltiy)
 * 
 *  3. For the enqueue function the function prints that it is inserting the item that was passed in instead of the location of where the data actually got saved. This is a big problem because this will make the function look like it is doing what is expected to when in reality it is only printing the value passed in. EX. cout << "Inserting " << item << '\n'; instead of cout << "Inserting " << arr[rear] << '\n'; (After the item was inserted)
 * (Lack Maintainabiltiy)
 * 
 *  4. Another Mistake that I found was that within their destructor they used delete arr instead of delete []arr which actually deletes the entire array instead of just the memory pointed to by arr.(memory leak/Inefficient)
 * 
 *  5. The last poor decision choice that they made was that they did not initialize their array to default values. If they did it would have been easier to debug their code as to why something was happening. (Lack Maintainability)
 * 
 * 
 * An Entra one Just in case one is not considered poor programming practice
 *  6. Poor decision choice for the peek function was to return a numeric_limits<int>::min() instead of a simple -1, 0 or 1. Making invalid returns simple makes the debbugging simpler to understand (Lack Maintainability)
*/

// main function
int main()
{
    // call your test functions here!
    /**/
    testDequeueEmpty();
    testDequeueFull();
    testEnqueueEmpty();
    testEnqueueFull();
    testPeekEmpty();
    testPeekFull();
    testSize();
    testIsEmpty();
    testIsFull();
    return 0;
}

