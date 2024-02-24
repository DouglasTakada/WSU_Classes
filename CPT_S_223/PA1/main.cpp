
/*ADVANTAGES/DISADVANTAGES LINKED LIST
* The advantages of using a linked list for the data structrue involved with storing the commdands and discriptions was that it is a dynamic data structure so we can easily add and remove commands
* A disadvantage was when I was doing the logic for determining which commands has already been used, I had to go through the linked list every single time to figure out which one was used which was inefficient
* 
*/

/*ADVANTAGES/DISADVANTAGES ARRAY
* The advantages of using a dynamic array for the data strcuture involved with storing the user profile and user points was that I it was dynamically allocating (when it reached the array limit size it multiplied size and transfered the data. Another advantage was that becasue it was an array I could impliemnt a indexing function where I could easily navigate through the array
* The disadvantage was that I had to create my own data struct with the data that I wanted to save in the array. Another disadvantage was loading the data at the front which made it very inefficent O(n) instead of O(1)
* 
*/

#include "wrapper.hpp"

int main()
{
    wrapper Linux_game;
    Linux_game.run();
    return 0;
}