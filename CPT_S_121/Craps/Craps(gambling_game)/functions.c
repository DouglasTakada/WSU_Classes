
# include "functions.h"


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
int main_menu(void) {
	int num = 0;
	printf("Enter a number 1-4 to choose an option.\n\t");
	printf("1.) View game rules\n\t");
	printf("2.) Enter Bank Balance\n\t");
	printf("3.) Play Craps!\n\t");
	printf("4.) Exit Program\n\t");
	scanf("%d", &num);
	if (num < 1 || num > 4) {
		system("cls");
		printf("You entered a invalid option, try again.");
		main_menu();
		return -1;
	}
	return num;
}

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
void print_game_rules(void) {
	int temp = 0;
	printf("\n\tWeclome to the game of chance named Craps!\nThis game is played in casinos and back alleys throughout the world!\n\n\n");
	printf("Here are the rules:\n\tA player rolls two dice. Each die has six faces. These faces contain the numbers 1, 2, 3, 4, 5, and 6.\n\t");
	printf("After the dice have come to rest, the sum of the spots on the two upward faces is calculated.\n\t");
	printf("If the sum is 7 or 11 on the first throw, the player wins.\n\t");
	printf("If the sum is 2, 3, or 12 on the first throw (called \"craps\"),\n\t");
	printf("the player loses (i.e. the \"house\" wins).\n\t");
	printf("If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's \"point.\"\n\t");
	printf("To win, you must continue rolling the dice until you \"make your point.\"\n\t");
	printf("The player loses by rolling a 7 before making the point.\n\n\t");
	printf("When you are ready, enter any number\n");
	printf("\t(If you enter anything other than a number the program will not work.)\n\t\t");
	scanf("%d", &temp);
	system("cls");
}

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
double get_bank_balance(void) {
	double input = 0.0;
	printf("Please enter your bank balance you would like to start with: ");
	scanf(" %lf", &input);
	return input;
}

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
double get_wager_amount(void) {
	double input = 0.0;
	printf("\nPlease enter your wager amount for this game: ");
	scanf("%lf", &input);
	return input;
}

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
double check_wager_amount(double wager, double bbalance) {
	if (wager > bbalance) {
		printf("Your wager for this game is $%.2f but only have $%.2f in your bank. Your wager has been reset.\n", wager, bbalance);
		while (wager > bbalance) {
			wager = get_wager_amount();
		}
		return wager;
	}
	else {
		printf("Your wager for this game is $%.2f and currently have $%.2f in your bank. Good luck!\n", wager, bbalance);
		return wager;
	}
}

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
double update_wager_amount(double wager, double bbalance) {
	if (wager < bbalance) {
		double temp = 0.0;
		printf("Would you like to raise your bet for the next dice roll?\n");
		printf("If you'd like to raise your bet, enter the amount you would like to add to your wager\n");
		scanf("%lf", &temp);
		printf("Your bank balance is %.2f\n", bbalance);
		printf("Your wager for the next round is: %.2f\n", temp + wager);
		return temp + wager;
	}
}

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
int roll_die(int number_rolls) {

	int num = (rand() % 6) + 1;
	printf("Dice roll: %d\n", num);
	number_rolls++;
	return num;
}

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
int calculate_sum_die(int die1_value, int die2_value) {
	return die1_value + die2_value;
}

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
int is_win_or_loss_point(int sum_die) {

	if (sum_die == 11 || sum_die == 7) {
		printf("You won this round! Congrats\n");
		return 1;
	}
	else if (sum_die == 2 || sum_die == 3 || sum_die == 12) {
		printf("CRAPS! Darn you lost! The house wins this round\n\n");
		return 0;
	}
	else {
		printf("You didn't win or lose this round\n");
		return sum_die;
	}
}

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
int is_point_loss_or_neither(int sum_die, int pt_value, int number_rolls, double wager, double bank_balance) {
	int die3 = roll_die(number_rolls);
	int die4 = roll_die(number_rolls);
	printf("New sum: %d\n", die3 + die4);
	printf("Point Value = %d\n", pt_value);
	sum_die = die3 + die4;

	if (sum_die == pt_value) {
		printf("You won congrats!\n");
		return 1;
	}
	else if (sum_die == 7) {
		printf("You got 7 so you lost\n");
		return 0;
	}
	else {

		wager = update_wager_amount(wager, bank_balance);
		int temp = is_point_loss_or_neither(sum_die, pt_value, number_rolls, wager, bank_balance);

		return temp;
	}

}

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
int calculate_add_or_subtract(int point_value, int successive_rolls) {
	if (point_value == 1 || successive_rolls == 1) {
		return 1;// means add the wager
	}
	else if (point_value == 0 || successive_rolls == 0) {
		return 0;// means subtract the wager
	}
	return -1;
}

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
double adjust_bank_balance(double bank_balance, double wager, int add_or_subtract) {
	if (add_or_subtract == 1) {
		printf("Your bet was $%.2f on this game and you won! Your bank balance is now $%.2f\n", wager, bank_balance + wager);
		return bank_balance + wager;
	}
	else if (add_or_subtract == 0) {
		printf("Your bet was $%.2f on this game and you lost. Your bank balance is now $%.2f\n", wager, bank_balance - wager);
		return bank_balance - wager;
	}
	return -1;
}

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
void chatter_messages(int number_rolls, int point_value, double bank_balance) {
	if (number_rolls > 6 && number_rolls < 10) {
		printf("Oh, you're going for broke, huh?");
	}
	else if (point_value == 6) {
		printf("Someone walks up and wispers in your ear \"Bet big this round\"\n");
	}
	if (bank_balance > 100) {
		printf("Whoa you have a lot of money, I bet if you put it all in youll win big!\n");
	}
	if (bank_balance < 10) {
		printf("You dont have a lot of money, try betting a little less\n");
	}

}