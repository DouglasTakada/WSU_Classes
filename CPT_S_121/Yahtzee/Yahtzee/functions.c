#include "functions.h"

/*
	Name: DT
	Function: dancing(void)
	date: 10/26/2021
	Input parameters: void
	Returns: Nothing
	Description: This function animates stick figures dancing
	Preconditions: The preconditions that are needed are the start of the program
	Postconditions: The stick figures bust out some sick moves
*/
void dancing(void) {
	for (int i = 0; i < 25; i++) {
		printf("\n   O     O     O     O ");
		printf("\n   |/    |/    |/    |/");
		printf("\n  /|    /|    /|    /| ");
		printf("\n  /\\    /\\    /\\    /\\");
		system("cls");
		printf("\n   O     O     O     O");
		printf("\n  \\|    \\|    \\|    \\|  ");
		printf("\n   |\\    |\\    |\\    |\\");
		printf("\n   /\\    /\\    /\\    /\\");
		system("cls");
	}
}

/*
	Name: DT
	Function: main_menu(void)
	date: 10/26/2021
	Input parameters: void
	Returns: Returns an integer that represents the option the user entered
	Description: This function asks the user for input for three options and returns the valid chosen option
	Preconditions: The preconditions that are needed are the start of the program
	Postconditions: Returns the valid option chosen from the user and clears the screen
*/
int main_menu(void) {
	int num = 0;
	printf("Enter a number 1-3 to choose an option.\n\t");
	printf("1.) View game rules\n\t");
	printf("2.) Play Yahtzee!\n\t");
	printf("3.) Exit Program\n\t");
	scanf("%d", &num);
	while (num != 1 && num != 2 && num != 3) {
		system("cls");
		printf("You entered a invalid option, try again.");
		num = main_menu();
		return -1;
	}
	return num;
}

/*
	Name: DT
	Function: game_rules()
	date: 10/26/2021
	Input parameters: void
	Returns: Nothing
	Description: This function prints out all of the rules of the game in a readable format
	Preconditions: The precondition that are needed are the start of the program
	Postconditions: Prints the game rules and after the user presses a key, clears the screen
*/
void game_rules(void) {
	system("cls");
	printf("\tWeclome to the game of chance named Yahtzee!\n\n");
	printf("\tYahtzee is a two player game so go grab a friend!\n");
	printf("\tThe point of the game is to outscore your opponent by the last 13th round.\n");
	printf("\tTo do this you want to roll your die to score as many points as possbile per round.\n");
	printf("\tPoints are awarded based on the kind of combinations you roll with your die.\n");
	printf("\n\tThe challenge of this game is that the combinations that awards you points\n\t\tcan only be awarded once except for the combination of Yahtzee.\n");
	printf("\tThe second challenge is that you have the choice to reroll your die three times per round\n\t\tand keep some die from rerolling to gain as many points as possible.\n");
	printf("\n\tIf you score more than 63 points in the upper section you get 35 bonus points!\n");
	printf("\n\tHere are the 13 ways you can score points:\n");
	printf("\n\n\t\t\t|Upper Section|\n");
	printf("\n\tName: Aces |\n\tDie combination: The dices with the number one |\n\tPoints: The sum of all face values of 1 |\n");
	printf("\n\tName: Twos |\n\tDie combination: The dices with the number Two |\n\tPoints: The sum of all face values of 2 |\n");
	printf("\n\tName: Threes |\n\tDie combination: The dices with the number three |\n\tPoints: The sum of all face values of 3 |\n");
	printf("\n\tName: Fours |\n\tDie combination: The dices with the number four |\n\tPoints: The sum of all face values of 4 |\n");
	printf("\n\tName: Fives |\n\tDie combination: The dices with the number five |\n\tPoints: The sum of all face values of 5 |\n");
	printf("\n\tName: Sixes |\n\tDie combination: The dices with the number six |\n\tPoints: The sum of all face values of 6|\n");
	printf("\n\n\t\t\t|Lower Section|\n");
	printf("\n\tName: Three of a kind|\n\tDie combination: Three dice with the same face |\n\tPoints: The sum of all face values on the 5 dice |\n");
	printf("\n\tName: Four of a kind|\n\tDie combination: Four dice with the same face |\n\tPoints: The sum of all face values on the 5 dice |\n");
	printf("\n\tName: Chance |\n\tDie combination: Can be used for any sequence of dice |\n\tPoints: The sum of all face values on the 5 dice |\n");
	printf("\n\tName: Full House |\n\tDie combination: One pair(Two dice with the same face)\n\t\tand a three-of-a-kind(Three dice with the same face) |\n\tPoints: 25 |\n");
	printf("\n\tName: Small Straight |\n\tDie combination: A sequence of four dice (dice in squential order) |\n\tPoints: 30 |\n");
	printf("\n\tName: Large Straight |\n\tDie combination: A sequence of five dice (dice in squential order) |\n\tPoints: 40 |\n");
	printf("\n\tName: Yahtzee |\n\tDie combination: Five-of-a-kind (Five dice with the same face) |\n\tPoints: 50 |\n");
	printf("\n\tScroll up to view all the rules!\n\n");
	system("pause");
	system("cls");
}

/*
	Name: DT
	Function: Roll_all_die(int die_values[],int arr_size)
	date: 10/26/2021
	Input parameters: int die_values[],int arr_size
	Returns: Nothing
	Description: This function rolls all five of the die
	Preconditions: The precondition is the start of the program and
		proper intialzation of the paramaters
	Postconditions: All of the die values are given new values
*/
void roll_all_die(int die_values[], int arr_size) {
	for (int index = 1; index < arr_size; index++) {
		die_values[index] = (rand() % 6) + 1;
	}

}

/*
	Name: DT
	Function: print_die_values(int_die_values[], int arr_size)
	date: 10/26/2021
	Input parameters: int die_values[],int arr_size
	Returns: Nothing
	Description: This function prints the players die values
	Preconditions: The precondition is the start of the program and
		proper initialzation of the paramaters
	Postconditions: All of the die values are printed for the user
*/
void print_die_values(int die_values[], int arr_size) {
	printf("Here are your die values:\n");
	for (int index = 1; index < arr_size; ++index) {
		printf("\tDie [%d]: %d\n", index, die_values[index]);
	}
}

/*
	Name: DT
	Function:  print_options(void)
	date: 10/26/2021
	Input parameters: void
	Returns: The valid option 1-14
	Description: This function prints and returns the options
		for the player to score or re-roll
	Preconditions: The precondition is the start of the program
	Postconditions: The users valid option is returned
*/
int print_options(void) {
	printf("Select an option from below\n");
	printf("\t\tUpper Section\n");
	printf("\t 1. Aces           |\t2. Twos\n");
	printf("\t 3. Threes         |\t4. Fours\n");
	printf("\t 5. Fives          |\t6. Sixes\n\n");
	printf("\t\tLower Section\n");
	printf("\t7. Three of a kind |\t8. Four of a kind\n");
	printf("\t9. Chance          |\t10. Full House\n");
	printf("\t11. Small Stright  |\t12. Large Straight\n");
	printf("\t13. Yahtzee        |\t14. *Re-roll*\n");
	int temp = 0;

	scanf("%d", &temp);

	if (temp < 1 || temp > 14) { // Checks to make sure option is 1-14
		system("cls");
		printf("You have entered an invald option. Please try again.\n");
		print_options();
	}
	return temp;
}

/*
	Name: DT
	Function: check_option(int option, int valid_score_option[])
	date: 10/26/2021
	Input parameters: int option, int valid_score_option[]
	Returns: If the option is valid the it returns 1 otherwise returns 0
	Description: This functions checks if the user has chosen an option they
		have already selected in a previous round excecpt Yahtzee and re-roll
	Preconditions: The start of the program and proper initialization of
		paramater variables
	Postconditions: Determines if the option that the user has input is valid
		in  this round
*/
int check_options(int option, int valid_score_option[]) {
	if (option == 13 || option == 14) {
		system("cls");
		return 1;
	}
	if (valid_score_option[option] == 0) {
		valid_score_option[option] += 1;
		system("cls");
		return 1;
	}
	else {
		system("cls");
		printf("\tYou have already chosen this option!\n\tYou cannot choose an option more than once except to reroll and Yahtzee!\n");
		return 0;
	}

}

/*
	Name: DT
	Function: frequency
	date: 10/26/2021
	Input parameters: int freq[],int die_values[])
	Returns: Nothing
	Description: This function counts the number of values there are on
		all five of the die
	Preconditions: The start of the program and initalization of
		the variables
	Postconditions: Has array that counts what values were rolled
*/
void frequency(int freq[], int die_values[]) {
	for (int i = 1; i < 6; i++) {
		freq[i] = 0;
	}
	for (int i = 1; i < 6; i++) {
		freq[die_values[i]] += 1;
	}
}

/*
	Name: DT
	Function: aces(int freq[], int score_card[])
	date: 10/26/2021
	Input parameters:int freq[], int score_card[]
	Returns: Nothing
	Description: This function calculates how much the player should
		 be rewarded based on what the player rolled
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The function indirectly returns number of points
		to award the player
*/
void aces(int freq[], int score_card[]) {
	score_card[1] = freq[1];
}

/*
	Name: DT
	Function: tows(int freq[], int score_card[])
	date: 10/26/2021
	Input parameters:int freq[], int score_card[]
	Returns: Nothing
	Description: This function calculates how much the player should
		 be rewarded based on what the player rolled
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The function indirectly returns number of points
		to award the player
*/
void twos(int freq[], int score_card[]) {
	score_card[2] = freq[2] * 2;
}

/*
	Name: DT
	Function: threes(int freq[], int score_card[])
	date: 10/26/2021
	Input parameters:int freq[], int score_card[]
	Returns: Nothing
	Description: This function calculates how much the player should
		 be rewarded based on what the player rolled
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The function indirectly returns number of points
		to award the player
*/
void threes(int freq[], int score_card[]) {
	score_card[3] = freq[3] * 3;
}

/*
	Name: DT
	Function: fours(int freq[], int score_card[])
	date: 10/26/2021
	Input parameters:int freq[], int score_card[]
	Returns: Nothing
	Description: This function calculates how much the player should
		 be rewarded based on what the player rolled
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The function indirectly returns number of points
		to award the player
*/
void fours(int freq[], int score_card[]) {
	score_card[4] = freq[4] * 4;
}

/*
	Name: DT
	Function: fives(int freq[], int score_card[])
	date: 10/26/2021
	Input parameters:int freq[], int score_card[]
	Returns: Nothing
	Description: This function calculates how much the player should
		 be rewarded based on what the player rolled
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The function indirectly returns number of points
		to award the player
*/
void fives(int freq[], int score_card[]) {
	score_card[5] = freq[5] * 5;
}

/*
	Name: DT
	Function: sixes(int freq[], int score_card[])
	date: 10/26/2021
	Input parameters:int freq[], int score_card[]
	Returns: Nothing
	Description: This function calculates how much the player should
		 be rewarded based on what the player rolled
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The function indirectly returns number of points
		to award the player
*/
void sixes(int freq[], int score_card[]) {
	score_card[6] = freq[6] * 6;
}

/*
	Name: DT
	Function: three_of_a_kind(int freq[], int score_card[], int die_values[])
	date: 10/26/2021
	Input parameters:int freq[], int score_card[], int die_values[]
	Returns: Nothing
	Description: This function calculates how much the player should
		 be rewarded based on what the player rolled
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The function indirectly returns number of points
		to award the player
*/
void three_of_a_kind(int freq[], int score_card[], int die_values[]) {
	int sum = 0;
	for (int i = 1; i < 6; i++) {
		if (freq[i] >= 3) {
			for (int i = 1; i < 6; i++) {
				sum = die_values[i] + sum;
			}
			score_card[7] = sum;
		}
	}
}

/*
	Name: DT
	Function: four_of_a_kind(int freq[], int score_card[], int die_values[])
	date: 10/26/2021
	Input parameters:int freq[], int score_card[], int die_values[]
	Returns: Nothing
	Description: This function calculates how much the player should
		 be rewarded based on what the player rolled
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The function indirectly returns number of points
		to award the player
*/
void four_of_a_kind(int freq[], int score_card[], int die_values[]) {
	int sum = 0;
	for (int i = 1; i < 6; i++) {
		if (freq[i] >= 4) {
			for (int i = 1; i < 6; i++) {
				sum = die_values[i] + sum;
			}
			score_card[8] = sum;
		}
	}
}

/*
	Name: DT
	Function: chance(int die_values[], int score_card[])
	date: 10/26/2021
	Input parameters: int die_values[], int score_card[]
	Returns: Nothing
	Description: This function calculates how much the player should
		 be rewarded based on what the player rolled
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The function indirectly returns number of points
		to award the player
*/
void chance(int die_values[], int score_card[]) {
	int sum = 0;
	for (int i = 1; i < 6; i++) {
		sum = die_values[i] + sum;
	}
	score_card[9] = sum;
}

/*
	Name: DT
	Function: full_house(int freq[], int score_card[])
	date: 10/26/2021
	Input parameters:int freq[], int score_card[]
	Returns: Nothing
	Description: This function calculates how much the player should
		 be rewarded based on what the player rolled
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The function indirectly returns number of points
		to award the player
*/
void full_house(int freq[], int score_card[]) {// Think if what frequency array will look like
	int check2 = 0, check3 = 0;// check if there is a pair and a three of a kinds and then run it through the if statement

	for (int i = 1; i < 6; i++) {
		if (freq[i] == 2) {
			check2 = 1;
		}
		if (freq[i] == 3) {
			check3 = 1;
		}
	}
	if (check2 == 1 && check3 == 1) {
		score_card[10] = 25;
	}
	else {
		score_card[10] = 0;
	}

}

/*
	Name: DT
	Function: small_straight(int freq[], int score_card[])
	date: 10/26/2021
	Input parameters:int freq[], int score_card[]
	Returns: Nothing
	Description: This function calculates how much the player should
		 be rewarded based on what the player rolled
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The function indirectly returns number of points
		to award the player
*/
void small_straight(int freq[], int score_card[]) {
	if (freq[1] == 1 && freq[2] == 1 && freq[3] == 1 && freq[4] == 1) {
		score_card[11] = 40;
	}
	else if (freq[2] == 1 && freq[3] == 1 && freq[4] == 1 && freq[5] == 1) {
		score_card[11] = 40;
	}
	else if (freq[3] == 1 && freq[4] == 1 && freq[5] == 1 && freq[6] == 1) {
		score_card[11] = 40;
	}
}

/*
	Name: DT
	Function: large_straight(int freq[], int score_card[])
	date: 10/26/2021
	Input parameters:int freq[], int score_card[]
	Returns: Nothing
	Description: This function calculates how much the player should
		 be rewarded based on what the player rolled
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The function indirectly returns number of points
		to award the player
*/
void large_straight(int freq[], int score_card[]) {
	int counter = 0;

	for (int i = 1; i < 6; i++) {
		if (freq[i] != 1) {
			counter++;
		}
	}
	if (counter > 1) {
		score_card[12] = 0;
	}
	else {
		score_card[12] = 40;
	}
}

/*
	Name: DT
	Function: yahtzee(int freq[], int score_card[])
	date: 10/26/2021
	Input parameters:int freq[], int score_card[]
	Returns: Nothing
	Description: This function calculates how much the player should
		 be rewarded based on what the player rolled
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The function indirectly returns number of points
		to award the player
*/
void yahtzee(int freq[], int score_card[]) {
	for (int index = 1; index < 6; index++) {
		if (freq[index] == 5) {
			score_card[13] += 50;
		}
	}
}

/*
	Name: DT
	Function: reroll(int die_values[])
	date: 10/26/2021
	Input parameters: int die_values[]
	Returns: Nothing
	Description: This function asks the user what die they would like to reroll
	Preconditions: The precondition is the start of the program
		and proper initaliation of the variables
	Postconditions: The dice that the user wished to reroll are rerolled
*/
void reroll(int die_values[]) {
	char temp = '\0';
	int index = 1;
	system("cls");
	printf("What die would you like to reroll?\n");
	printf("Enter y or n\n");
	for (; index < 6; index++) {
		printf("die #%d: %d?\n", index, die_values[index]);
		scanf(" %c", &temp);
		while (temp != 'y' && temp != 'Y' && temp != 'n' && temp != 'N') {
			printf("Please enter a valid option\n");
			printf("die #%d: %d?\n", index, die_values[index]);
			printf("enter y or n\n");
			scanf(" %c", &temp);
		}
		if (temp == 'y' || temp == 'Y') {
			die_values[index] = (rand() % 6) + 1;
		}
		temp = '\0';
	}
	printf("Here are your new die values:\n");
	for (index = 1; index < 6; index++) {
		printf("die #%d: %d\n", index, die_values[index]);
	}
}

/*
	Name: DT
	Function: print_score_card(int score_card[])
	date: 10/26/2021
	Input parameters:int score_card[]
	Returns: Nothing
	Description: This function prints out the players score card
	Preconditions: The precondition is the start of the program
		and proper initaiation of the variables
	Postconditions: The scores of the player is printed
*/
void print_score_card(int score_card[]) {
	printf("Here is your scorecard:\n");
	printf("\t\tUpper Section\n");
	printf("\t Aces: %d           |\t Twos: %d \n", score_card[1], score_card[2]);
	printf("\t Threes: %d         |\t Fours: %d \n", score_card[3], score_card[4]);
	printf("\t Fives: %d          |\t Sixes: %d \n\n", score_card[5], score_card[6]);
	printf("\t\tLower Section\n");
	printf("\tThree of a kind: %d |\tFour of a kind: %d \n", score_card[7], score_card[8]);
	printf("\tChance: %d          |\tFull House: %d \n", score_card[9], score_card[10]);
	printf("\tSmall Stright: %d   |\tLarge Straight: %d \n", score_card[11], score_card[12]);
	printf("\t\tYahtzee: %d \n", score_card[13]);
}

/*
	Name: DT
	Function: print_scores(int p1_score_card[], int p2_score_card[],
		int scor1m int)
	date: 10/26/2021
	Input parameters:int p1_score_card[], int p2_score_card[]
	Returns: Nothing
	Description: This function calculates how much each player scored
	and prints their scores and prints who the winner is
	Preconditions: The precondition is the start of the program
		and proper initiation of the variables
	Postconditions: The function prints the scores of each player and
		prints who the winner is
*/
void print_scores(int p1_score_card[], int p2_score_card[]) {
	int index = 1, score1 = 0, score2 = 0;
	for (; index < 6; index++) {
		score1 += p1_score_card[index];
		score2 += p2_score_card[index];
	}
	if (score1 >= 63) {
		score1 += 35;
	}
	if (score2 >= 63) {
		score2 += 35;
	}
	for (; index < 7; index++) {
		score1 += p1_score_card[index];
		score2 += p2_score_card[index];
	}
	printf("Player 1 scored: %d\n", score1);
	printf("Player 2 scored: %d\n", score2);

	if (score1 > score2) {
		printf("Congrats player 1 you won!\n");
	}
	else if (score1 < score2) {
		printf("Congrats player2 you won!\n");
	}
	else {
		printf(" Wow! It was a tie! You both lost\n");
	}
	system("pause");
}