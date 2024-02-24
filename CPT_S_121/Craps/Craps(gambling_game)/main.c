/*
* Author: Douglas Takada
* Date: October, 2nd, 2021
* Description: This program allows the the user the play the game craps.
*				It does so by having various functions and repeating the computational functions
*				that show weather the player is doing well or not and prints out statements to
*				tell the user how they are doing.
*/

#define GAME_RULES 1
#define BANK_BALANCE 2
#define PLAY_GAME 3
#define EXIT 4
#include "functions.h"

int main(void) { // The starting point to all c programs
	srand(time(0)); // To calculate "random numbers" SHOULD ONLY be called ONCE PERIOD!

	int number_rolls = 0, main = 0, die1_value = 0, die2_value = 0, sum_die = 0, //initializing integer variables to be called
		pt_value = 0, point_value = 0, successive_rolls = 0, add_or_subtract = 0;
	double bank_balance = 0.0, wager = 0.0; // initializing double variables to be called

	while (main != 4) { //while loop that stays in the loop unless the user chooses the option to exit
		main = main_menu(); //The left side of the equation calls the function on the right side of 
							//the equation and the value that the function returns is what the variable
							//is set equal to
		switch (main)
		{
		case GAME_RULES:
			print_game_rules(); //prints game rules
			break;
		case BANK_BALANCE:
			bank_balance = get_bank_balance(); // Asks for starting bank balance and the left side of the 
							//equation calls the function on the right side of the equation and the value 
							//that the function returns is what the variable is set equal to
			break;
		case PLAY_GAME:
			system("cls"); // clears the command line of previous prints and inputs so it is cleaner
			if (bank_balance == 0.0) {// If the player wants to play the game before they have set their bank balance it asks the user to input a bank balance
				bank_balance = get_bank_balance();//The left side of the equation calls the function on the right side of 
							//the equation and the value that the function returns is what the variable
							//is set equal to
			}
			chatter_messages(number_rolls, point_value, bank_balance); // prints out 'random messages' based on given inputs and outputs
			wager = get_wager_amount(); //asks for the wager amount and saves that value into wager
			wager = check_wager_amount(wager, bank_balance); // Double checks that the wager that they set is less than bank balance
			die1_value = roll_die(number_rolls); // rolls dice
			die2_value = roll_die(number_rolls); // rolls dice
			chatter_messages(number_rolls, point_value, bank_balance); // prints out 'random messages' based on given inputs and outputs
			sum_die = calculate_sum_die(die1_value, die2_value); // Calculates the sum of the die
			pt_value = sum_die; // Sets the point value that the player got on the first roll to another variable so it ba compared to later
			point_value = is_win_or_loss_point(sum_die); // Based on their rolls prints out statements depending on if they won or not
			if (point_value > 1) // The sum of the die can never be 1 or 0 and when that is what the point value is, that means that they won or lost
			{
				chatter_messages(number_rolls, point_value, bank_balance); // prints out 'random messages' based on given inputs and outputs
				wager = update_wager_amount(wager, bank_balance); // if the wager that they bet is good then it adds the additional wager to the total wager amount
				wager = check_wager_amount(wager, bank_balance); //double checks what they are betting is less than their bank balance 
				successive_rolls = is_point_loss_or_neither(sum_die, pt_value, number_rolls, wager, bank_balance); // Does all the computation for the successive rolls in one place
			}
			add_or_subtract = calculate_add_or_subtract(point_value, successive_rolls); //sets the output of the function equal to a integer that showsh whether to add the wager or take it away from the balance
			bank_balance = adjust_bank_balance(bank_balance, wager, add_or_subtract); // based on how the game ended add or subtract the wager from the bank balance
			//chatter_messages(number_rolls, point_value, bank_balance); // prints out 'random messages' based on given inputs and outputs

			break;
		case EXIT: // User entered 4 to exit the program
			printf("Thanks For Playing!"); //End of program statement
			return 0;
			break;
		}
	}
	return 0;
}