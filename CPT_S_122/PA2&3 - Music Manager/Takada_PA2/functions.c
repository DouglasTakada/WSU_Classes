#include "functions.h"


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
void shuffle(Node** pHead) {
	int lenList = 0, numSongs = 1, counter = 0, i = 0;
	Node* curNode = *pHead;
	Node* corNode = *pHead;
	Node* headNode = *pHead;
	int* arrList = (int*)malloc(sizeof(int)*lenList);//create dynamic array that is length of list
	int randNum = 0;
	while (curNode != NULL) {//Find length of list
		curNode = curNode->nextNode;
		lenList++;
	}
	while (i != lenList) {//Reseting all values to 0 should only happen once
		arrList[i] = 0;
		i++;
	}
	
	while (numSongs <= lenList) {
		while (arrList[randNum] == 1) {//Keep looking for a node that has yet to be played
			randNum = (rand() % (lenList) + 1);//randNum = (rand() % ((lenList - 1)) + 1);
		}
		arrList[randNum] = 1;//Also Need to increment the array index

		counter = 1;
		corNode = headNode;
		while (counter <= randNum) {//Get to correct node to read all data
			corNode = corNode->nextNode;
			counter++;
		}//After this the counter should be at the correct Node
		//next would be to display all info in the node
		if (corNode != NULL) {
			randNum++;
			printf("\n\tSong Number: %d\n\tSongs Played: %d", randNum,numSongs);
			randNum--;
			numSongs++;//Means the song was played
			printRec(corNode);
			Sleep(2000);
			system("cls");
		}
	}
}

void toLower(char str[]) {
	for (int i = 0; str[i]; i++) {
		str[i] = tolower(str[i]);
	}
}

char* onlyAlpha(char str[]) {
	char temp[30] = "";
	strcpy(temp, str);
	int i = 0, j =0;
	for (i = 0, j = 0; temp[i] != '\0'; i++)
	{
		if ((temp[i] >= 'A' && temp[i] <= 'Z') || (temp[i] >= 'a' && temp[i] <= 'z'))
		{
			temp[j] = temp[i];
			j++;
		}
	}
	temp[j] = '\0';
	return temp;
}


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
void sort(Node** pHead) {
	int option = 0;
	//Determine sorting method: 1. artist name(A-Z) 2. Album title(A->Z) 3. Rating (1 ->5) 4. times played (Largest -> Smallest)
	printf("Here are the options to sort your playlist:\n"
		"\t1. Sorted based on artist(A-Z)\n\t2. Sorted based on album(A-Z)"
		"\n\t3. Sort based on rating (1-5)\n\t4. Sort based on times played\n"
	);
	scanf("%d", &option);
	while (option!= 1 && option != 2 && option!= 3 && option != 4) {
		printf("Enter a integer to decide on how you would like to sort the list\n\t");
		printf("Here are the options to sort your playlist:\n"
			"\t1.Sorted based on artist(A-Z)\n\t2.Sorted based on album(A-Z)"
			"\n\t3. Sort based on rating (1-5)\n\t4. Sort baed on times played\n"
		);
		scanf("%d", &option);
	}
	//For each case I need the length of the list for bubble sort so I will use a counter
	Node* curNode = *pHead;
	int lenList = 0, counter = 0;
	while (curNode != NULL){
		lenList++;
		curNode = curNode->nextNode;
		}
	curNode = (*pHead)->nextNode;
	Node* prevNode = (*pHead);
	Record tempRec = { "","","","",{0,0},0,0 };
	char art1[20] = "", art2[20] = "";
	switch (option) {
	case 1://Artist Name
		while (counter <= lenList) {//Compare one node to the one next to it
			curNode = (*pHead)->nextNode;
			prevNode = *pHead;
			while (curNode != NULL) {// delete any non-character in string " , " and " \" "
				strcpy(art1,onlyAlpha(curNode->data.artist));
				strcpy(art2, onlyAlpha(prevNode->data.artist));
				toLower(art1);//converts every characters into lower case
				toLower(art2);
				
				if (strcmp(art1, art2) < 0) {
					tempRec = prevNode->data;
					prevNode->data = curNode->data;
					curNode->data = tempRec;
				}
				prevNode = curNode;
				curNode = curNode->nextNode;
			}
			counter++;
		}
		break;
	case 2: //Album Title
		while (counter <= lenList) {//Compare one node to the one next to it
			curNode = (*pHead)->nextNode;
			prevNode = *pHead;
			while (curNode != NULL) {// delete any non-character in string " , " and " \" "
				strcpy(art1, onlyAlpha(curNode->data.albumTitle));
				strcpy(art2, onlyAlpha(prevNode->data.albumTitle));
				toLower(art1);//converts every characters into lower case
				toLower(art2);

				if (strcmp(art1, art2) < 0) {
					tempRec = prevNode->data;
					prevNode->data = curNode->data;
					curNode->data = tempRec;
				}
				prevNode = curNode;
				curNode = curNode->nextNode;
			}
			counter++;
		}
		break;
	case 3: //Rating
		while (counter <= lenList) {//Compare one node to the one next to it
			curNode = (*pHead)->nextNode;
			prevNode = *pHead;
			while (curNode != NULL) {// delete any non-character in string " , " and " \" "
				if (curNode->data.rating>prevNode->data.rating) {
					tempRec = prevNode->data;
					prevNode->data = curNode->data;
					curNode->data = tempRec;
				}
				prevNode = curNode;
				curNode = curNode->nextNode;
			}
			counter++;
		}
		break;
	case 4: //Times played
		while (counter <= lenList) {//Compare one node to the one next to it
			curNode = (*pHead)->nextNode;
			prevNode = *pHead;
			while (curNode != NULL) {// delete any non-character in string " , " and " \" "
				if (curNode->data.timesPlayed < prevNode->data.timesPlayed) {
					tempRec = prevNode->data;
					prevNode->data = curNode->data;
					curNode->data = tempRec;
				}
				prevNode = curNode;
				curNode = curNode->nextNode;
			}
			counter++;
		}
		break;
	}
}


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
int deleteNode(Node** pHead, char* songTitle) {
	
	Node* curNode = *pHead;
	int found = 0, success = 0;
	if (*pHead == NULL) {
		printf("This list is currently empty thus no node can be deleted.\n");
	}
	else {
		while (curNode != NULL && found != 1) {
			if (strcmp(curNode->data.songTitle, songTitle) == 0) {
				found = 1;
				Node* prevNode = curNode->prevNode;
				if (curNode->nextNode == NULL) {//End of list
					curNode->prevNode = NULL;
					free(curNode);//empty list
					printf("You have deleted the last song in the playlist\n");
				}
				else {
					Node* deleteNode = curNode;
					curNode = curNode->nextNode;
					if (prevNode == NULL) {//if the node we want to delete is at the begginning
						curNode->prevNode = NULL;
						*pHead = curNode;//sets the first node to the next node
					}
					else {//not at the begginning
						curNode->prevNode = prevNode;
						prevNode->nextNode = curNode;
					}
					free(deleteNode);
				}
			}
			if (found == 0) {
				curNode = curNode->nextNode;
			}
		}
		if (found == 1) {
			printf("The song title was found and succesfully deleted\n");
			success = 1;
		}
		else {
			printf("We could not find a match for the song title you entered\n");
		}
	}
	return success;
}


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
int insert(Node** pHead, Record newRec) {
	int success = 0, bad = 0;
	if (newRec.rating<1 || newRec.rating>5) {
		printf("your rating is invalid and you must change your rating between 1-5\n");
		bad++;
	}
	if (newRec.timesPlayed <= 0 ) {
		printf("your times played is invalid and must be a positive integer\n");
		bad++;
	}
	if (bad!= 0) {
		printf("The data was not put into the list as it was invalid");
		return success;
	}
	Node* newNode = makeNode(newRec);
	if (*pHead == NULL) {
		*pHead = newNode;
		success = 1;
	}
	else {
		newNode->nextNode = *pHead;//points to previous node in list
		(*pHead)->prevNode = newNode;//from the previous node points to reccent node
		(*pHead) = newNode;
		success = 1;
	}
	return success;
}

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
int mainMenu(void) {
	int option = 0;
	printf("PLease select one of the following options");
	printf("\n\t(1) load\n\t(2) store\n\t(3) display\n\t(4) insert\n\t(5) delete\n\t"
		"(6) edit\n\t(7) sort\n\t(8) rate\n\t(9) play\n\t(10) shuffle\n\t(11) exit\n\t");
	scanf("%d", &option);
	system("cls");
	while (option != 1 && option != 2 && option != 3 && option!= 4 && option!= 5
		&& option != 6 && option!= 7&&option != 8 && option != 9 &&option!=10&& option != 11) {
		printf("\n\n\t You have entered a invalid option please try again\n");
		printf("\n\t(1) load\n\t(2) store\n\t(3) display\n\t(4) insert\n\t(5) delete\n\t"
			"(6) edit\n\t(7) sort\n\t(8) rate\n\t(9) play\n\t(10) shuffle\n\t(11) exit\n\t");
		scanf("%d", &option);
		system("cls");
	}
	return option;
}


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
Node* makeNode(Record tempRec) {
Node* newNode = (Node*)calloc(1, sizeof(Node));
//put data in node
strcpy(newNode->data.albumTitle, tempRec.albumTitle);
strcpy(newNode->data.artist, tempRec.artist);
strcpy(newNode->data.genre, tempRec.genre);
strcpy(newNode->data.songTitle, tempRec.songTitle);
newNode->data.rating = tempRec.rating;
newNode->data.songLength.minute = tempRec.songLength.minute;
newNode->data.songLength.seconds = tempRec.songLength.seconds;
newNode->data.timesPlayed = tempRec.timesPlayed;
newNode->nextNode= NULL;
newNode->prevNode = NULL;
return newNode;
}


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
int InsertFront(Node** pHead, FILE* playlist)
{
	int success = 0;
	char line[80] = "";
	Record tempRec = {"","","","",{0,0},0,0};
	while(fgets(line, 80, playlist) != NULL) {
		tempRec = parseLine(line, tempRec);// saves data into struct
		Node* newNode = makeNode(tempRec);// create node
		
		//connect node onto the node that previously pHead
		if (*pHead == NULL) {
			*pHead = newNode;
		}
		else {
			newNode->nextNode = *pHead;//points to previous node in list
			(*pHead)->prevNode = newNode;//from the previous node points to reccent node
			(*pHead) = newNode;
			success = 1;
		}
	}
	return success;
}


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
Record parseLine(char line[], Record data) {
	char* token = "";
	strcpy(data.artist, "");
	token = strtok(line, ",");
	if (token[0] == 34) {
		strcat(data.artist, token);
		strcat(data.artist, ",");
		strcat(data.artist, strtok(NULL, ","));
	}
	else {
		strcpy(data.artist, token);
	}
	token = strtok(NULL, ",");
	strcpy(data.albumTitle, token);
	token = strtok(NULL, ",");
	strcpy(data.songTitle, token);
	token = strtok(NULL, ",");
	strcpy(data.genre, token);
	token = strtok(NULL, ":");
	data.songLength.minute = atoi(token);
	token = strtok(NULL, ",");
	data.songLength.seconds = atoi(token);
	token = strtok(NULL, ",");
	data.timesPlayed = atoi(token);
	token = strtok(NULL, "\n");
	data.rating = atoi(token);

	return data;

}


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
void printList(Node* pHead) {
	Node* currNode = pHead;
	char userArtist[30] = "";
	int temp = 0;
	printf("\t1. Print all records.\n\t2. Print all records that match an artist.");
	scanf("%d", &temp);
	switch (temp) {
	case 1://Print all records
		while (currNode->nextNode != NULL) {//Get to very last node then start reading
			currNode = currNode->nextNode;
		}
		while (currNode != NULL) {
			printRec(currNode);
			currNode = currNode->prevNode;
		}
		break;
	case 2://print records that match a artist
		temp = 0;
		printf("\tEnter the artist you would like to see the records of:\n\t");

		getchar();
		gets(userArtist);
		while (currNode != NULL) {
			if (strcmp(userArtist, currNode->data.artist) == 0) {
				printRec(currNode);
				temp++;
			}
			currNode = currNode->nextNode;
		}
		if (temp == 0) {
			printf("We could not find any records of that artist");
		}
		break;

	}
}


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
int store(Node* pHead) {
	FILE* outfile = fopen("musicPlayList.csv", "w");
	Node* currNode = pHead;
	int success = 0;
	if (currNode == NULL) {
		printf("You do not have a playlist loaded, and thus cannot store anything\n");
		return success;
	}
	if (outfile != NULL) {
		while (currNode->nextNode != NULL) {//Get to very last node then start reading
			currNode = currNode->nextNode;
		}
		while (currNode != NULL) {//Prints in the same order
			fprintf(outfile, "%s,%s,%s,%s,%d:%d,%d,%d\n",
				(currNode)->data.artist, (currNode)->data.albumTitle, (currNode)->data.songTitle, (currNode)->data.genre,
				(currNode)->data.songLength.minute, (currNode)->data.songLength.seconds, (currNode)->data.timesPlayed, (currNode)->data.rating);
			currNode = currNode->prevNode;
		}
		success = 1;
	}
	return success;
}


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
void editRecord(Node** pHead) {
	Node* currNode =  *pHead;
	char userArtist[30] = "";
	int temp = 0;
	printf("\tEnter the artist you would like to change the records of:\n\t");

	getchar();
	gets(userArtist);
	while (currNode != NULL) {
		if (strcmp(userArtist, currNode->data.artist) == 0) {
			editAtt(currNode, userArtist);
			temp++;
		}
		currNode = currNode->nextNode;
	}
	if (temp == 0) {
		printf("We could not find any records of that artist\n");
	}
}


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
void editAtt(Node* currNode) {
	int temp = 0, min = 0, sec = 0;
	char userIn[30] = "";
	printf("What would you like to change in this record?");
	printf("\n (Choose from 0-7)");
	printf("\n0. No change\n1. Artist: %s\n2. Album: %s\n3. Song Name: %s\n4. Genre: %s\n5. Duration: %d:%d\n6. Times Played: %d\n7. Rating: %d\n\n",
		currNode->data.artist, currNode->data.albumTitle, (currNode)->data.songTitle, (currNode)->data.genre,
		(currNode)->data.songLength.minute, (currNode)->data.songLength.seconds, (currNode)->data.timesPlayed, (currNode)->data.rating);
	scanf("%d", &temp);
	switch (temp) {
	case 0:
		//Do nothing
		break;
	case 1://Artist
		printf("Enter the new artist here:");
		getchar();
		gets(userIn);
		strcpy((currNode)->data.artist,userIn);
		break;
	case 2://album
		getchar();
		gets(userIn);
		printf("Enter the new album here:");
		strcpy((currNode)->data.albumTitle, userIn);
		break;
	case 3://Song
		printf("Enter the new song title here:");
		getchar();
		gets(userIn);
		strcpy((currNode)->data.songTitle,userIn);
		break;
	case 4://Genre
		printf("Enter the new genre here:");
		getchar();
		gets(userIn);
		strcpy((currNode)->data.genre, userIn);
		break;
	case 5://Duration
		printf("\nEnter minutes here: ");
		scanf("%d", &min);
		printf("\nEnter your seconds here: ");
		scanf("%d", &sec);
		(currNode)->data.songLength.minute = min;
		(currNode)->data.songLength.seconds = sec;
		break;
	case 6://Times PLayed
		printf("\nEnter new times played here: ");
		scanf("%d", &temp);
		(currNode)->data.timesPlayed = temp;
		break;

	case 7://Rating
		printf("\nEnter new ratings here: ");
		scanf("%d", &temp);
		(currNode)->data.rating = temp;
		break;
	}
	printf("\nHere are your new changes:\n");
	printRec(currNode);
	system("pause");
}


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
void rateRec(Node** pHead) {
	Node* currNode = *pHead;
	char userArtist[30] = "";
	int temp = 0;
	printf("\tEnter the artist you would like to change the records of:\n\t");

	getchar();
	gets(userArtist);
	while (currNode != NULL) {
		if (strcmp(userArtist, currNode->data.artist) == 0) {
			printRec(currNode);
			printf("\nEnter your new ratings here: ");
			scanf("%d", &temp);
			(currNode)->data.rating = temp;
			printf("\nHere are your new changes:\n");
			printRec(currNode);
			system("pause");
			temp++;
		}
		currNode = currNode->nextNode;
	}
	if (temp == 0) {
		printf("We could not find any records of that artist\n");
	}
}


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
void printRec(Node* currNode) {
	printf("\nArtist: %s\nAlbum: %s\nSong Name: %s\nGenre: %s\nDuration: %d:%d\nTimes Played: %d\nRating: %d\n\n",
		(currNode)->data.artist, (currNode)->data.albumTitle, (currNode)->data.songTitle, (currNode)->data.genre,
		(currNode)->data.songLength.minute, (currNode)->data.songLength.seconds, (currNode)->data.timesPlayed, (currNode)->data.rating);
}


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
void playSong(Node** pHead) {
	int temp = 0, counter = 0;
	char userSong[20] = "";
	Node* currNode = *pHead;
	Node* trackNode = NULL;
	Node* trackNode0 = NULL;
	printf("1. Play songs in order\n2. Search for song name and start there\n");
	scanf("%d", &temp);
	switch (temp) {
	case 1:
		while (currNode->nextNode != NULL) {//Get to very last node then start reading
			currNode = currNode->nextNode;
		}
		while (currNode != NULL) {
			printRec(currNode);
			Sleep(2000);
			system("cls");
			currNode = currNode->prevNode;
		}
		//get to the very last song of the list then start printing from there
		break;
	case 2:
		printf("What song would you like to start listening to?");
		getchar();
		gets(userSong);
		while (currNode != NULL) {//Ask for user input for a specific song title and then print that node then remeber
									//their pointers so I can print them later
			if (strcmp(userSong, currNode->data.songTitle) == 0) {
				printRec(currNode);//print first case
				Sleep(2000);
				system("cls");
				trackNode = currNode;
				trackNode0 = currNode;
			}
			currNode = currNode->nextNode;
		}
		if (trackNode->prevNode != NULL) {
			while (trackNode->prevNode != NULL) {
				trackNode = trackNode->prevNode;
				printRec(trackNode);//print second case And next cases
				Sleep(2000);
				system("cls");
			}
		}
		else {//This means that the previous node is null and thus you are at the end of the list

		}
		if (trackNode0->nextNode != NULL) {
			while (trackNode0->nextNode != NULL) {
				trackNode0 = trackNode0->nextNode;
				printRec(trackNode0);//print second case And next cases
				Sleep(2000);
				system("cls");
			}
		}
		
		break;
	}
}