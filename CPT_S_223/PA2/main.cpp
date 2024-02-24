#include "AVLTree.h"
int main(void) {
    int ascending[50] = { 0 };
    int descending[50] = { 0 };
    int random[50] = { 0 };


    //Create arrays of 1 - 100 of odd numbers, one ascending one descending and one random
    for (int i = 0; i < 50; i++) {
        ascending[i] = i + i + 1;
        descending[49 - i] = ascending[i];
        random[i] = ascending[i];
    }

    //randomizes the random array
    random_shuffle(std::begin(random), std::end(random));

    //creates three AVL trees
    AVLTree<int> ascendingAVL;
    AVLTree<int> descendingAVL;
    AVLTree<int> randomAVL;

    //inserts the three data sequences into the three AVL trees, seperately.
    for (int i = 0; i < 50; i++) {
        ascendingAVL.insert(ascending[i]);
        descendingAVL.insert(descending[i]);
        randomAVL.insert(random[i]);
    }



    cout << "Height of Ascending AVL Tree: "<< ascendingAVL.height();
    cout<< "\n";
    cout << "Height of Descending AVL Tree: "<< descendingAVL.height();
    cout << "\n";
    cout << "Height of Random AVL Tree: "<< randomAVL.height();
    cout << "\n\n";

    //print result of validate for each AVL tree
    cout << "Result of calling validate function for Ascending AVL Tree: " << ascendingAVL.validate();
    cout << "\n";
    cout << "Result of calling validate function for Descending AVL Tree: " << descendingAVL.validate();
    cout << "\n";
    cout << "Result of calling validate function for Random AVL Tree: " << randomAVL.validate();
    cout << "\n\n";

    //create a frequency array of what output we should expect from the output of the function contains in each AVL tree.
    bool containsTest[101] = { 0 };
    
    //What we will be using to check all the other AVL tree contains function. This is a frequency array that says every odd number is one and all evens are 0's
    for (int i = 0; i < 101; i++) {
        if (i % 2 != 0) {
            containsTest[i] = 1;
        }
        
    }

    //For each AVL tree loop over numbers 1 - 100 and call contains() function for each number
    for (int i = 1; i < 101; i++) {//Saves all the return values of the contains function for each of the AVL Trees
        if (ascendingAVL.contains(i) != containsTest[i]) {
            cout << "\nMy AVL Implementation is wrong";
            break;
        }
        if (descendingAVL.contains(i) != containsTest[i]) {
            cout << "\nMy AVL Implementation is wrong";
            break;
        }
        if (randomAVL.contains(i) != containsTest[i]) {
            cout << "\nMy AVL Implementation is wrong";
            break;
        }
        if (i == 100) {
            cout << "\nMy AVL Implementation is correct";
        }
    }


    cout << "\n\n";
    ascendingAVL.printLevelOrder();
    cout << "\n";
    descendingAVL.printLevelOrder();
    cout << "\n";
    randomAVL.printLevelOrder();

    return 0;
}