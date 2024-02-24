#include "header.hpp"
#include "bst.hpp"

int main(void) {
	
	BST<char, string> morseCodeTree;
	morseCodeTree.print();

	ifstream input;
	input.open("Convert.txt");
	morseCodeTree.convertToMorse(input);
	input.close();

	return 0;
}