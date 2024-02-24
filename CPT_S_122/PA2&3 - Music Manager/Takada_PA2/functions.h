#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct duration {
	int minute;
	int seconds;
}Duration;

typedef struct record {
	char artist[20];
	char albumTitle[30];
	char songTitle[30];
	char genre[10];
	Duration songLength;
	int timesPlayed;
	int rating;
}Record;

typedef struct node {
	Record data;
	struct node* nextNode;
	struct node* prevNode;
}Node;


/*
* void shuffle(Node** pHead)
* Date Created: 2/13/2022
* Date Last Modified: 2/13/2022
* Description: This function shuffles the songs randomly and plays the songs
* Input Parameter: Node** pHead
* Returns: nothing
* Preconditions: The function must be called
* Postconditions: The playlist is played randomly and returns to the main menu
*/
void shuffle(Node** pHead);

char* onlyAlpha(char str[]);


/*
* Function: void sort(Node** pHead)
* Date Created: 2/13/2022
* Date Last Modified: 2/13/2022
* Description: This function sorts the list in four different ways based on user input
* : 1. artist name(A-Z) 2. Album title(A->Z) 3. Rating (1 ->5) 4. times played (Largest -> Smallest)
* Input Parameter: Node** pHead, char* songTitle
* Returns: nothing
* Preconditions: The function must be called
* Postconditions: The list is sorted in the fashion the user requested
*/
void sort(Node** pHead);


/*
* Function: int deleteNode(Node** pHead, char* songTitle)
* Date Created: 2/13/2022
* Date Last Modified: 2/13/2022
* Description:This function deletes a node based on the given song title the user inputs
* Input Parameter: Node** pHead, char* songTitle
* Returns: integer based on if the function was successful or not
* Preconditions: The function must be called
* Postconditions: based on the list and the user input, the node is deleted
*/
int deleteNode(Node** pHead, char* songTitle);


/*
* Function: int insert(Node** pHead, Record newRec)
* Date Created: 2/13/2022
* Date Last Modified: 2/13/2022
* Description:This function allows the user to input valid data
* Input Parameter: Node** pHead, Record newRec
* Returns: integer based on if the function was successful or not
* Preconditions: The function must be called
* Postconditions: the node is inserted based on if it was given valid data
*/
int insert(Node** pHead, Record newRec);

/*
* Function: int mainMenu(void)
* Date Created: 1/30/2022
* Date Last Modified: 2/2/2022
* Description:This function takes care of invalid input, prints the options and retursn the option number
* Input Parameter: Nothing
* Returns: Valid option number
* Preconditions: The function must be called
* Postconditions: A valid option is chosen from user and returned
*/
int mainMenu(void);


/*
* Function: Node* makeNode(Record tempRec)
* Date Created: 1/30/2022
* Date Last Modified: 2/2/2022
* Description: When this function is called a new node in the heap and is allocated space
*				this function also initializes the data from its parameter
* Input Parameter: Record tempRec
* Returns: This function returns the new node
* Preconditions: The function must be called
* Postconditions: A new node is created and is returned with the data that was passed into the function
*/
Node* makeNode(Record newRec);


/*
* Function: int InsertFront(Node** pHead, FILE* playlist)
* Date Created: 1/30/2022
* Date Last Modified: 2/2/2022
* Description: When this function is called it reads each line and for each line it create a new node
*				in which it stores its information
* Input Parameter: Node** pHead, FILE* playlist
* Returns: This function returns if inserting at the front was a success or not
* Preconditions: The function must be called
* Postconditions: A list is created or a node is attached to the list at the front
*/
int InsertFront(Node** pHead, FILE* playlist);


/*
* Function: Record parseLine(char line[], Record data
* Date Created: 1/30/2022
* Date Last Modified: 2/2/2022
* Description: This function looks at the line passed through the function and parses the data and
*				saves it into a temporary record struct
* Input Parameter: char line[], Record data
* Returns: This function returns the data struct that it was able to parse
* Preconditions: The function must be called
* Postconditions: The data struct is returned
*/
Record parseLine(char line[], Record newRec);


/*
* Function: void printList(Node* pHead)
* Date Created: 1/30/2022
* Date Last Modified: 2/2/2022
* Description: This function asks to print all records or only data from a artist
* Input Parameter: Node* pHead
* Returns: Nothing
* Preconditions: The function must be called
* Postconditions: All the data in the list is printed or only from a artist is printed
*/
void printList(Node* pHead);


/*
* Function: int store(Node* pHead)
* Date Created: 1/30/2022
* Date Last Modified: 2/2/2022
* Description: This function opens the musicPlayList.csv file to write and writes all
*				the data that is stored in each node. It is printed in the correct order
* Input Parameter: Node* pHead
* Returns: If it successfully uploaded into the file it returns 1 otherwise 0
* Preconditions: The function must be called
* Postconditions: All the data in the list is printed into the output file and the outputfile is closed
*/
int store(Node* pHead);


/*
* Function: void editRecord(Node** pHead)
* Date Created: 1/30/2022
* Date Last Modified: 2/2/2022
* Description: This function asks what artist they would like to edit
* Input Parameter: Node* pHead
* Returns: Nothing
* Preconditions: The function must be called
* Postconditions: The specified artists records are changed
*/
void editRecord(Node** pHead);


/*
* Function: editAtt(Node* currNode)
* Date Created: 1/30/2022
* Date Last Modified: 2/2/2022
* Description: This function asks what artist they would like to edit
* Input Parameter: Node* currNode
* Returns: Nothing
* Preconditions: The function must be called
* Postconditions: A attribute of the record is changed and saved into the record
*/
void editAtt(Node* currNode);


/*
* Function: void rateRec(Node** pHead)
* Date Created: 1/30/2022
* Date Last Modified: 2/2/2022
* Description: This function asks what artists records they would like to change their rating on
* Input Parameter: Node** pHead
* Returns: Nothing
* Preconditions: The function must be called
* Postconditions: A the rating of the specified artists records is changed and saved back into the linked list
*/
void rateRec(Node** pHead);


/*
* Function: void printRec(Node* currNode)
* Date Created: 1/30/2022
* Date Last Modified: 2/2/2022
* Description: This function prints the record that is passed through the parameter
* Input Parameter: Node* currNode
* Returns: Nothing
* Preconditions: The function must be called
* Postconditions: The data for the specified node is printed
*/
void printRec(Node* currNode);


/*
* Function: playSong(Node** pHead)
* Date Created: 1/30/2022
* Date Last Modified: 2/2/2022
* Description: This function asks the user if they would like to play the playlist from the begginning
*				Or starting with a song that they can search for
* Input Parameter: Node** pHead
* Returns: Nothing
* Preconditions: The function must be called
* Postconditions: The song is displayed and then the nex song is displayed to simulate listening to music
*/
void playSong(Node** pHead);


#endif
