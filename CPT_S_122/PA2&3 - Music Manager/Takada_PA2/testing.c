#include "testing.h"


void testInsert(void) {
	//To test an insertion you need a record to insert.
	printf("testing insert function...\n");
	Sleep(1000);
	int success = 0;
	Node* testHead = NULL;
	Record testRec = { "\"Perry, Katy\"", "Witness", "Chained to the Rhythm",
	"pop", {4,36}, -1, 6};
	success = insert(&testHead, testRec);
	if (success == 1) {
		printf("Test was successful\n");
	}
	else {
		printf("Test failed, check insert function for more details\n");
	}
}

void testDelete(void) {
	//to Test a delete function you need a node to delete
	printf("testing delete node function...\n");
	int success = 0;
	char songTitle[30] = "Chained to the Rhythm";
	Record testRec = { "\"Perry, Katy\"", "Witness", "Chained to the Rhythm",
		"pop", {4,36}, 3, 5};
	Node* testHead = makeNode(testRec);
	success = deleteNode(&testHead, songTitle);
	if (success = 1) {
		printf("Test for delete function was successful\n");
	}
	else {
		printf("Test for delete function failed, check deleteNode function for more details\n");
	}
}

void testShuffle(void) {
	// hard code
	printf("\n----TESTING SHUFFLE SONGS FXN----\n");
	int arr[3] = {3, 1, 2 };	// order of songs to play...
	Record p1 = { "\"Perry, Katy\"", "Witness", "Chained to the Rhythm",
	"pop", {2,30}, 3, 3 };
	Record p2 = { "\"West, Kanye\"", "Pablo", "Ultralight Beam",
	"rap", {4,20}, 3, 2 };
	Record p3 = { "Bieber", "Boop", "Beep",
	"pop", {9,11}, 3, 4 };
	Node* pTest = { NULL };
	int numSongs = 0, size = 3,rand_num = 0, counter = 1, index = 0;

	printf("Songs in the playlist:\n");
	insert(&pTest, p1);
	insert(&pTest, p2);
	insert(&pTest, p3);
	Node* curNode = pTest;
	printf("Shuffling songs in (3, 1, 2) order:\n");
	while (numSongs < size) {
		curNode = pTest;
		counter = 1;
		while (counter < arr[index]) {//Get to correct node to read all data
			curNode = curNode->nextNode;
			counter++;
		}
		printf("Song Number: %d\n", arr[index]);
		printRec(curNode);
		Sleep(2000);
		index++;
		numSongs++;
	}
}