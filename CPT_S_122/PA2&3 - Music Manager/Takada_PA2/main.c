/*
* Douglas Takada
* 1/28/2022
* Assignment: PA2 - Digital Music Manager (DMM) Part 1.
* 1. Text based interface with the following options:
			(1) load, (2) store, (3) display, (6) edit, (8) rate, (9) play, and (11) exit
*/

#include "functions.h"
#include "testing.h"

int main(int argc, char* argv[]) {

	int option = 0, tempint = 0, oneOrTwo = 0;
	char tempstr[30] = "", songTitle[20] = "";
	Record tempRec = { "","","","",{0,0},0,0 },newRec = { "","","","",{0,0},0,0 };;
	Node* pHead = NULL;
	FILE* infile = NULL;

	int test = 0;
	printf("Would you like to run tests?\n\t1. Yes\n\t2. No\n\t");
	scanf("%d", &test);
	if (test == 1) {// run tests
		testInsert();
		testDelete();
		testShuffle();
		system("pause");
		system("cls");
	}
		printf("\tWelcome to Digital Music Manager (DMM)!\n\t");
	option = mainMenu();
	while (option != -1) {
		switch (option) {
		case 1://load
			infile = fopen("musicPlayList.csv", "r");
			if (infile ==NULL) {
				printf("Failed to read from given file...\n");
			}
			if (InsertFront(&pHead, infile) == 1) {
				printf("\n\tThe songs have successfully loaded "
					"into the main playlist\n");
				system("pause");
			}
			fclose(infile);
			option = mainMenu();
			break;
		case 2://store
			if (store(pHead) == 1) {
				printf("\n\tThe songs have successfully loaded "
					"into the musicPlayList.csv file\n");
				system("pause");
			}
			option = mainMenu();
			break;
		case 3://display
			printList(pHead);
			option = mainMenu();
			break;
		case 4://insert
			printf("Enter your new Record information here:\n (put it in parenthesis with a comma if there is a first and last name)\n"
				"\tnew Artist:");
			getchar();
			gets(tempstr);
			strcpy(newRec.artist, tempstr);
			printf("\n\tNew album title:");
			gets(tempstr);
			strcpy(newRec.albumTitle, tempstr);
			printf("\n\tNew song title:");
			gets(tempstr);
			strcpy(newRec.songTitle, tempstr);
			printf("\n\tNew song genre:");
			gets(tempstr);
			strcpy(newRec.genre, tempstr);
			printf("Number of minutes:");
			scanf("%d", &tempint);
			newRec.songLength.minute = tempint;
			printf("Number of seconds:");
			scanf("%d", &tempint);
			newRec.songLength.seconds = tempint;
			printf("Number of times played:");
			scanf("%d", &tempint);
			newRec.timesPlayed = tempint;
			printf("Rating:");
			scanf("%d", &tempint);
			newRec.rating = tempint;
			insert(&pHead, newRec);
			printf("Here is your new list:\n\n");
			printList(pHead);
			option = mainMenu();
			break;
		case 5://delete
			printf("Enter the song title you would like to delete\n");
			getchar();
			gets(songTitle);
			deleteNode(&pHead,songTitle);
			option = mainMenu();
			break;
		case 6://edit
			editRecord(&pHead);
			option = mainMenu();
			break;
		case 7://sort
			sort(&pHead);
			option = mainMenu();
			break;
		case 8://rate
			rateRec(&pHead);
			option = mainMenu();
			break;
		case 9://play
			playSong(&pHead);
			option = mainMenu();
			break;
		case 10://shuffle
			shuffle(&pHead);
			option = mainMenu();
			break;
		case 11://exit and writes records to the music playlist
			if (pHead != NULL && store(pHead) == 1) {
				printf("\n\tThe songs have been successfully loaded "
					"into the musicPlayList.csv file and exited\n");
			}
			option = -1;
			break;
		}
	}
	return 0;
}