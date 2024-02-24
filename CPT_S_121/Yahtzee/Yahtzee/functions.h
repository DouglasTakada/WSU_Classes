#define _CRT_SECURE_NO_WARNINGS
#ifndef EQUATIONS_H
#define EQUATIONS_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

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
void dancing(void);

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
int main_menu(void);

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
void game_rules(void);

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
void roll_all_die(int die_values[], int arr_size);

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
void print_die_values(int die_values[], int arr_size);

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
int  print_options(void);

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
int check_options(int option, int valid_score_option[]);

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
void frequency(int freq[], int die_values[]);

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
void aces(int freq[], int core_card[]);

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
void twos(int freq[], int score_card[]);

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
void threes(int freq[], int score_card[]);

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
void fours(int freq[], int score_card[]);

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
void fives(int freq[], int score_card[]);

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
void sixes(int freq[], int score_card[]);

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
void three_of_a_kind(int freq[], int score_card[], int die_values[]);

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
void four_of_a_kind(int freq[], int score_card[], int die_values[]);

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
void chance(int die_values, int score_card[]);

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
void full_house(int freq[], int score_card[]);

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
void small_straight(int freq[], int score_card[]);

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
void large_straight(int freq[], int score_card[]);

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
void yahtzee(int freq[], int score_card[]);

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
void reroll(int die_values[]);

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
void print_score_card(int score_card[]);

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
void print_scores(int p1_score_card[], int p2_score_card[]);

#endif