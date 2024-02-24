#include "testQueue.h"

/*       Test ID: testDequeueEmpty
          Unit: queue::dequeue() 
        Description: test to determine if dequeue() prints "UnderFlow Program Terminated" when queue object is empty 
          Test steps: 
1.    Construct an empty queue object 
2.    Invoke queue::dequeue () 
3.    Conditionally evaluate the statement printed to console by queue::dequeue () 
          Test data: size = 10 
          Precondition: queue object is empty 
          Postcondition: queue object is still empty 
        Expected result: queue is empty; "UnderFlow Program Terminated" is printed in commandline
          Actual result: queue is empty; prints "removing 0"
          Status: Failed
*/ 
void testDequeueEmpty(void){
    queue test;
    test.dequeue();
}


/*       Test ID: testDequeueFull
          Unit: queue::dequeue() 
        Description: test to determine if dequeue() prints "Removing" arr[front] when queue object contains elements
          Test steps: 
1.    Construct an empty queue object 
2.    Invoke queue::enqueue(3)
3.    Invoke queue::enqueue(2)
4.    Invoke queue::enqueue(3)
5.    Invoke queue::enqueue(4)
6.    Invoke queue::enqueue(5)
7.    Invoke queue::enqueue(6)
8.    Invoke queue::enqueue(7)
9.    Invoke queue::enqueue(8)
10.   Invoke queue::enqueue(9)
11.   Invoke queue::enqueue(10)
12.   Invoke queue::dequeue() 
3.    Conditionally evaluate the statement printed to console by queue::dequeue () 
          Test data: size = 10 
          Precondition: queue object contains 10 values 
          Postcondition: queue object contains 9 values
        Expected result: queue is still size 10 with 9 elements; prints "Removing " arr[front] (in this case it will be 3)
          Actual result: queue is still size 10 with 9 elements; prints "Removing 1
          Status: Failed
*/ 
void testDequeueFull(void){//removing 9 instead of 10
    queue test;
    test.enqueue(3);
    test.enqueue(2);
    test.enqueue(3);
    test.enqueue(4);
    test.enqueue(5);
    test.enqueue(6);
    test.enqueue(7);
    test.enqueue(8);
    test.enqueue(9);
    test.enqueue(10);
    test.dequeue();
}

/*       Test ID: testEnqueueEmpty
          Unit: queue::enqueue() 
        Description: test to determine if enqueue() prints "Inserting" item when queue object is empty 
          Test steps: 
1.    Construct an empty queue object 
2.    Invoke queue::enqueue(1) 
3.    Conditionally evaluate the statement printed to console by queue::enqueue () 
          Test data: size = 10 
          Precondition: queue object is empty 
          Postcondition: queue object contains 1 element
        Expected result: queue contains 1 elemet of value 1; prints "Inserting 1" to command line
          Actual result: queue contains 1 elemet of value 1; prints "Inserting 1" to command line
          Status: Passed
*/ 
void testEnqueueEmpty(void){
    queue test;
    test.enqueue(1);
}


/*       Test ID: testEnqueueFull
          Unit: queue::enqueue() 
        Description: test to determine if enqueue() prints "OverFlow\nProgram Terminated" when user tries to insert more elements than the array size 
          Test steps: 
1.    Construct an empty queue object with size 2
2.    Invoke queue::enqueue(1) 
3.    Invoke queue::enqueue(2) 
4.    Invoke queue::enqueue(3) 
5.    Conditionally evaluate the statement printed to console by queue::enqueue () 
          Test data: size = 3 
          Precondition: queue object has size restriction 2 with two elements inside
          Postcondition: queue object contains still only contains two elements after the third enqueue call
          Expected result: queue contains 2 element of value 1 and 2; "OverFlow Program Terminated" is printed in commandline
          Actual result: queue contains 2 element of value 1 and 2; "OverFlow Program Terminated" is printed in commandline
          Status: Passed
*/ 
void testEnqueueFull(void){
    queue test(2);
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);

}

/*       Test ID: testPeekEmpty
          Unit: queue::peek() 
        Description: test to determine if peek() prints "UnderFlow\nProgram Terminated" when user tries to use the function without any elements inside 
          Test steps: 
1.    Construct an empty queue object
2.    Invoke queue::peek()
3.    Conditionally evaluate the statement printed to console by queue::peek () 
          Test data: size = 3 
          Precondition: queue object is empty 
          Postcondition: queue object is still empty
          Expected result: queue is empty; "Underflow Program Terminated" is printed in commandline
          Actual result: Printed nothing
          Status: Failed
*/ 
void testPeekEmpty(void){
    queue test;
    test.peek();
}

/*       Test ID: testPeekFull
          Unit: queue::peek() 
        Description: test to determine if peek() returns the integer value at the end of queue
          Test steps: 
1.    Construct an queue object
2.    Invoke queue::enqueue(1)
3.    Invoke queue::enqueue(2)
4.    Invoke queue::enqueue(3)
5.    Invoke queue::enqueue(300)
6.    Invoke queue::peek()
7.    Conditionally evaluate the function through what it returns
          Test data: size = 4
          Precondition: 4 elements added to the queue
          Postcondition: still 4 elements in the queue
          Expected result: queue has 4 elements; the number 300 is returned
          Actual result: queue has 4 elements; the number 4 is returned
          Status: Failed
*/ 
void testPeekFull(void){
    queue test;
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    test.enqueue(300);
    cout<<test.peek()<<endl;
}

/*       Test ID: testSize
          Unit: queue::size() 
        Description: test to determine if size() returns the integer value at the end of queue
          Test steps: 
1.    Construct an queue object
2.    Invoke queue::enqueue(1)
3.    Invoke queue::enqueue(2)
4.    Invoke queue::enqueue(3)
5.    Invoke queue::enqueue(1300)
6.    Invoke queue::size()
7.    Conditionally evaluate the function through what it returns
          Test data: size = 4
          Precondition: 4 elements added to the queue
          Postcondition: still 4 elements in the queue
          Expected result: queue has 4 elements; the first number that is returned is 0 and the number 4 should be returned the second function call
          Actual result: queue has 4 elements; the first number returned is 1 instead of 0 and the number 5 is returned instead of 4
          Status: Failed
*/ 
void testSize(void){
    queue test;
    cout<<test.size()<<endl;
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    test.enqueue(1300);
    cout<<test.size()<<endl;
}

/*       Test ID: testIsEmpty
          Unit: queue::isEmpty() 
        Description: test to determine if isEmpty() returns the integer value at the end of queue
          Test steps: 
1.    Construct an queue object
2.    Invoke queue::enqueue(1)
3.    Invoke queue::isEmpty()
4.    Invoke queue::dequeue()
5.    Invoke queue::isEmpty()
6.    Conditionally evaluate the function through what it returns
          Test data: size = 1
          Precondition: 1 element added to the queue
          Postcondition: no elements in queue
          Expected result: queue has 0 elements; the first number returned is 0 and the second value returned is 1
          Actual result: both boolean expressions returned false(Two 0's) which is incorrect
          Status:  Failed
*/ 
void testIsEmpty(void){
    queue test;
    test.enqueue(1);
    cout<<test.isEmpty()<<endl;
    test.dequeue();
    cout<<test.isEmpty()<<endl;
}

/*       Test ID: testIsFull
          Unit: queue::isEmpty() 
        Description: test to determine if isEmpty() returns the boolean value we expect it to
          Test steps: 
1.    Construct an queue object of size 2
2.    Invoke queue::enqueue(1)
3.    Invoke queue::isfull()
4.    Invoke queue::enqueue(2)
5.    Invoke queue::isfull()
6.    Conditionally evaluate the function through what it returns
          Test data: size = 2
          Precondition: 1 element added to the queue
          Postcondition: 2 elements in queue
          Expected result: queue has 2 elements; the first expression is a false and the second value returned is true
          Actual result: queue has 2 elements; the first expression is a false and the second value returned is true
          Status: Passed
*/ 
void testIsFull(void){
    queue test(2);
    test.enqueue(1);
    cout<<test.isFull()<<endl;
    test.enqueue(2);
    cout<<test.isFull()<<endl;
}
