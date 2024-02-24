/*
* Author: Douglas Takada
* Date: October, 26th, 2021
* Description:		This program enables two people to play the game Yahtzee.
*				This program keeps track of the die that each plaer rolls,
*				their scores for and what options they have chosen to be awarded points
*				This program uses various loops and switch case statements with arrays
*				to indrectly change the values within the arrays.
*				This program first prompts the user for input where they can decide to:
*				1. read the game rules 2. play the the game and 3. exit the game.
*				From here the function goes on to call various functions to print the game
*				rules or play the game or exit the program.
*/

#include "functions.h"

//Defined global variables to improve readability
#define GAME_RULES 1 
#define PLAY_GAME 2
#define EXIT 3

int main(void) {
	//Initializes all of the arrays and variables I'm going to use for the program
	int main = 0, p1_die_values[6] = { 0 }, p1_score_card[14] = { 0 }, valid_score_option_p1[14] = { 0 },
		valid_score_option_p2[14] = { 0 }, p2_die_values[6] = { 0 }, p2_score_card[14] = { 0 },
		temp_score_numbers[14] = { 0 }, freq_p1[7] = { 0 }, freq_p2[7] = { 0 },
		size_p1_die = sizeof(p1_die_values) / 4, size_p2_die = sizeof(p2_die_values) / 4,
		option = 0, result = 0, total_rolls = 0, counter = 0, round = 1, round_over = 0;
	srand(time(0));// This enables me to be able to generate "random" numbers for the dicerolls

	while (main != 3) {//Loop for the main menu
		main = main_menu(); //calls the main_menu function and sets the option that the user inputs equal to main
		switch (main)// switch case to call certain functions depending on what the user input
		{
		case GAME_RULES:
			game_rules(); //prints the game rules
			break;

		case PLAY_GAME:
			round = 1;// starts a new game
			for (int i = 1; i < 14; i++) { // sets the arrays back to zero so the user can play more than once
				p1_score_card[i] = 0;
				valid_score_option_p1[i] = 0;
				p2_score_card[i] = 0;
				valid_score_option_p2[i] = 0;
				temp_score_numbers[i] = 0;
			}
			while (round < 14) { //while loop for the 13 rounds *it is 14 becasue I started the round at 1*
				round_over = 0;
				printf("The round for player 2 has ended. Press enter when player 1 is ready.\n");
				round++;

				system("pause");
				system("cls");
				roll_all_die(p1_die_values, size_p1_die);// rolls the die for player 1
				frequency(freq_p1, p1_die_values);// counts the number of numbers from skips first array index 0
				print_die_values(p1_die_values, size_p1_die);// prints the die values for player 1
				print_score_card(p1_score_card);// prints score card for player 1

				result = 0;
				while (result == 0) {
					option = print_options();// asks player 1 to input an option 
					result = check_options(option, valid_score_option_p1); // checks to see if the option is valid
				}

				while (round_over == 0) { // while loop to have until they choose an option that ends the round for them
					round_over = 1;
					counter = 0;
					switch (option) { //switch statement to call certain functions based on player 1 input
					case 1:
						aces(freq_p1, p1_score_card);
						break;
					case 2:
						twos(freq_p1, p1_score_card);
						break;
					case 3:
						threes(freq_p1, p1_score_card);
						break;
					case 4:
						fours(freq_p1, p1_score_card);
						break;
					case 5:
						fives(freq_p1, p1_score_card);
						break;
					case 6:
						sixes(freq_p1, p1_score_card);
						break;
					case 7:
						three_of_a_kind(freq_p1, p1_score_card, p1_die_values);
						break;
					case 8:
						four_of_a_kind(freq_p1, p1_score_card, p1_die_values);
						break;
					case 9:
						chance(p1_die_values, p1_score_card);
						break;
					case 10:
						full_house(p1_die_values, p1_score_card);
						break;
					case 11:
						small_straight(p1_die_values, p1_score_card);
						break;
					case 12:
						large_straight(p1_die_values, p1_score_card);
						break;
					case 13:
						yahtzee(p1_die_values, p1_score_card);
						break;
					case 14:
						round_over = 0; // reroll means the round is not over for them yet
						while (option == 14) { // loop for until they choose another option they cant exit the loop
							if (counter < 2) { // if statement to keep track of how many times the user rolled their die
								reroll(p1_die_values);// rerolls the die the player wants
								frequency(freq_p1, p1_die_values); //counts the frequency of the die
								counter++;// adds 1 to counter to keep track how many times they re-rolled
								result = 0;
								while (result == 0) {// while loop for player to choose a valid option
									option = print_options();
									result = check_options(option, valid_score_option_p1);
									frequency(freq_p1, p1_die_values);
								}
							}
							else {// This else statemnt is for if the player rolled three times this round
								printf("You already rolled three times for this round\n");
								option = -1;
								result = 0;
								// While loop the player can't exit out of until a valid option is chosen
								while (result == 0) {
									print_die_values(p1_die_values, size_p1_die);
									option = print_options();
									result = check_options(option, valid_score_option_p1);
								}
							}
						}
						break;
					}
				}
				/*This section is for the second player*/
				printf("The round for player 1 has ended. Press enter when player 2 is ready.\n");
				system("pause\n");
				system("cls");
				// sets things back to zero so no bad inputs
				option = 0, result = 0, counter = 0, round_over = 0;
				roll_all_die(p2_die_values, size_p2_die); //rolls all die for player 2
				frequency(freq_p2, p2_die_values);// skips first array index 0 and checks the frequency of the die values
				print_die_values(p2_die_values, size_p2_die);//prints die values for player 2
				print_score_card(p2_score_card);//prints score card for player 2
				result = 0;
				while (result == 0) {// same while loop as before for the user to input a valid option
					option = print_options();
					result = check_options(option, valid_score_option_p2);
				}
				// Another while loop to determine when player 2 selects an option that ends their round
				while (round_over == 0) {
					round_over = 1;
					counter = 0;
					//switch case to call certain functions for the functions to do caclulations for the player 2s points
					switch (option) {
					case 1:
						aces(freq_p2, p2_score_card);
						break;
					case 2:
						twos(freq_p2, p2_score_card);
						break;
					case 3:
						threes(freq_p2, p2_score_card);
						break;
					case 4:
						fours(freq_p2, p2_score_card);
						break;
					case 5:
						fives(freq_p2, p2_score_card);
						break;
					case 6:
						sixes(freq_p2, p2_score_card);
						break;
					case 7:
						three_of_a_kind(freq_p2, p2_score_card, p2_die_values);
						break;
					case 8:
						four_of_a_kind(freq_p2, p2_score_card, p2_die_values);
						break;
					case 9:
						chance(p2_die_values, p2_score_card);
						break;
					case 10:
						full_house(p2_die_values, p2_score_card);
						break;
					case 11:
						small_straight(p2_die_values, p2_score_card);
						break;
					case 12:
						large_straight(p2_die_values, p2_score_card);
						break;
					case 13:
						yahtzee(p2_die_values, p2_score_card);
						break;
					case 14:
						round_over = 0;
						//while loopto repreat until the option does not equal 14
						while (option == 14) {
							if (counter < 2) {// checks to see if player 2 has already rolled three times
								reroll(p2_die_values);// rerolls the values th player 2 wants to reroll
								frequency(freq_p2, p2_die_values);//checks the frequency of the new values of the dice
								counter++;//incriments the counter to keep track how many times player 2 has rerolled
								result = 0;// need to set equal to 0 so there are no bad inputs
								while (result == 0) {//while loop for until player 2 inputs a valid option
									option = print_options();
									result = check_options(option, valid_score_option_p2);
								}
							}
							else {// else statement for when player 2 already rolled three times
								printf("You already rolled three times\n");
								option = -1;
								result = 0;
								while (result == 0) {// while loop for until player 2 inputs a valid option
									print_die_values(p2_die_values, size_p2_die);
									option = print_options();
									result = check_options(option, valid_score_option_p2);
								}
							}
						}
						break;
					}
				}
			}
			//end of game and prints out the total scores of the players and prints who won this game
			print_scores(p1_score_card, p2_score_card);
			break;
		case EXIT: // case statement for when the user inputs option 3
			system("cls");
			dancing();// calls dancing function where stick figures dance
			printf("\t\tThanks For Playing!\n\n");
			break;
		}
	}

	return 0;//end of whole main function
}