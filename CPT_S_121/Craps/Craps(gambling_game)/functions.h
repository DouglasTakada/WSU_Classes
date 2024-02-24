#ifndef EQUATIONS_H
#define EQUATIONS_H

# define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

/*
	Name: DT
	Function: main_menu(void)
	date: 10/2
	Input parameters: void
	Returns: This function returns the integer value that the player inputs
	Description: This function prints statements for the user to read and to enter a nubmer to choose an option
	Preconditions: The preconditions that are needed are the start of the program
	Postconditions: The integer value of what the user inputed is returned
*/
int main_menu(void);

/*
	Name: DT
	Function: print_game_rules(void)
	date: 10/2
	Input parameters: void
	Returns: This function does not return a value
	Description: This function prints statements for the user to read and understand the rules of the game
	Preconditions: The preconditions that are needed are the start of the program and for the function to be called
	Postconditions: The rules of the game are printed and when the user is done can enter in a number and have the screen clear
	and go back to the menu
*/
void print_game_rules(void);

/*
	Name: DT
	Function: get_bank_balance(void)
	date: 10/2
	Input parameters: void
	Returns: This function returns a double value that represents the users initial bank blance for the game
	Description: This function prompts the user to input their starting bank balance for the game
	Preconditions: The preconditions that are needed are the start of the program and for the function to be called
	Postconditions: The bank balance of the user is returned and the user is sent back to the menu
*/
double get_bank_balance(void);

/*
	Name: DT
	Function: get_wager_amount(void)
	date: 10/2
	Input parameters: void
	Returns: This function returns a double value that represents the users intital wager amount in the beginning of the game
	Description: This function prompts the user to input how much they would like to bet on the first diceroll
	Preconditions: The preconditions that are needed are the start of the program and for the function to be called
	Postconditions: The intial wager amount is returned
*/
double get_wager_amount(void);

/*
	Name: DT
	Function: check_wager_amount(wager, bbalance)
	date: 10/2
	Input parameters: wager, bbalance
	Returns: This function returns a double value that represents the users wager amount
	Description: This function checks that the wager they set is less than their bank balance if it more than their banak balance then it prompts the user to enter a new wager amount
	Preconditions: The preconditions that are needed are the start of the program and for the function to be called
	Postconditions: The users wager amount will be less than their bank balance
*/
double check_wager_amount(double wager, double bbalance);

/*
	Name: DT
	Function: update_wager_amount(wager, bbalance)
	date: 10/2
	Input parameters: wager, bbalance
	Returns: This function returns a double value that represents the users total wager amount for the game in session
	Description: This function prompts the user to input how much more they would like to bet on the next diceroll and returns the sum
	Preconditions: The preconditions that are needed are the start of the program and for the function to be called
	Postconditions: The total wager amount is returned
*/
double update_wager_amount(double wager, double bbalance);

/*
	Name: DT
	Function: roll_die(number_rolls)
	date: 10/2
	Input parameters: number_rolls
	Returns: This function returns a integer value from 1 through 6 that represents the users dice rolls
	Description: This function uses the srand() and time() functions to come up with "random" values
	Preconditions: The preconditions that are needed are the start of the program and for the function to be called and for the srand(time(0)) to be called only once in main
	Postconditions: The users dice roll from 1 - 6 will be returned
*/
int roll_die(int number_rolls);

/*
	Name: DT
	Function: calculate_sum_die(die1_value, die2_value)
	date: 10/2
	Input parameters: die1_value, die2_value
	Returns: This function returns the sum of the dice for the given round as an integer
	Description: This function adds the values of the two rolled die and returns the sum
	Preconditions: The preconditions that are needed are the start of the program and for the function to be called
	Postconditions: The users sum of the dice roll will be returned
*/
int calculate_sum_die(int die1_value, int die2_value);

/*
	Name: DT
	Function: is_win_or_loss_point(sum_die)
	date: 10/2
	Input parameters: sum_die
	Returns: This function returns either 1, 0, or the sum of the dice
	Description: This prints out statements based on if you won or lost or neither and returns 1, 0 , or sum of dice respectivly
	Preconditions: The preconditions that are needed are the start of the program and for the function to be called and the sum of the dice
	Postconditions: The statement will be printed based on what happened in the game and either 1, 0 or the users sum of the dice roll will be returned
*/
int is_win_or_loss_point(int sum_die);

/*
	Name: DT
	Function: is_point_loss_or_neither(sum_die, pt_value number_rolls, wager, bank_balance)
	date: 10/2
	Input parameters: sum_die, pt_value number_rolls, wager, bank_balance
	Returns: This function returns either 1 or 0
	Description: This function calls to roll the dice, print out statements of the dice rolls, and add up the dice rolls sum and print it all onto the terminal
	This statement will constantly repreat itself until the user wins or loses. In the repeating process(when the user doesnt win or lose),
	it calls the update wager function to ask user to update wager every time
	Preconditions: The preconditions that are needed are the start of the program and for the function to be called and all of its prameters
	Postconditions: Depending on if you won or lost it returns a 1 or a 0
*/
int is_point_loss_or_neither(int sum_die, int pt_value, int number_rolls, double wager, double bank_balance);

/*
	Name: DT
	Function: calculate_add_or_subtract(point_value, successive_rolls)
	date: 10/2
	Input parameters: point_value, successive_rolls
	Returns: This function returns either 1 or 0
	Description: This function determintes weather add or subtract the amout that was bet on the round to be added or subtracted
	Preconditions: The preconditions that are needed are the start of the program and for the function to be called and all of its prameters
	Postconditions: Depending on if you won or lost it returns a 1 or a 0
*/
int calculate_add_or_subtract(int point_value, int successive_rolls);

/*
	Name: DT
	Function: adjust_bank_balance(bank_balance, wager, add_or_subtract)
	date: 10/2
	Input parameters: bank_balance, wager, add_or_subtract
	Returns: This function returns either your bank balance minus your wager or your bank balance plus your wager depending if you won or lost
	Description: This function prints out the statement on if you lost or not and updates you on your new bank balance
	Preconditions: The preconditions that are needed are the start of the program and for the function to be called and all of its prameters
	Postconditions: Depending on if you won or lost it returns your bank balance plus your wager or your bank balance minus your wager.
*/
double adjust_bank_balance(double bank_balance, double wager, int add_or_subtract);

/*
	Name: DT
	Function: chatter_messages(number_rolls, point_value, bank_balance)
	date: 10/2
	Input parameters: number_rolls, point_value, bank_balance
	Returns: void
	Description: This function prints out the statement on number of rolls, bank balance and your point value
	Preconditions: The preconditions that are needed are the start of the program and for the function to be called and all of its prameters
	Postconditions: Prints a message to the screen
*/
void chatter_messages(int number_rolls, int point_value, double bank_balance);

#endif