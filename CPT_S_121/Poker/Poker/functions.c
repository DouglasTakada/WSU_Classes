#include "functions.h"

/*
	Name: DT
	Function: menu(void)
	date: 12/1/2021
	Input parameters: void
	Returns: Option number
	Description: This function prompts the user to enter an option given the
				Three choices of view game rules, play Poker, or exit the game
	Preconditions: The preconditions that are needed are the start of the program
	Postconditions: The function returns a valid option from the user
*/
int menu(void) {
	int temp = 0;
	printf("Welcome, please enter a option:\n\t1. Game Rules\n\t2. Play Poker\n\t3. Exit Poker\n");
	scanf("%d", &temp);
	while (temp != 1 && temp != 2 && temp != 3) {
		system("cls");
		printf("You entered a invalid option, pleasre try again\n");
		printf("Please Enter a Valid Option:\n\t1. Game Rules\n\t2. Play Poker\n\t3. Exit Poker\n");
		scanf("%d", &temp);
	}
	return temp;
}

/*
	Name: Douglas Takda
	Function: game_rules(void)
	date: 12/1/2021
	Input parameters: Void
	Returns: Void
	Description: The function prints the rules of the game
	Preconditions: The preconditions that are needed are the start of the program
	Postconditions: The function prints the rules of the game
*/
void game_rules(void) {
	printf("Here are the game rules:\n");
	printf("\tThe goal of the game is to have a higher card value than your opponent.\n");
	printf("\tYou can acheive this by discarding and drawing up to three new cards.\n");
	printf("\tfrom the deck. You will have a chance to draw up to three new cards each\n");
	printf("\tround. You will only have two rounds where you will be able discard and draw\n");
	printf("\tHere is how the layout of the game:\n");
	printf("\tYou will be given five cards from the dealer one the first round.\n");
	printf("\tYou will then be prompted to view your cards and to decide which cards\n");
	printf("\tyou would like to keep or discard. This will happen for two rounds and whoever\n");
	printf("\thas a higher card ranking at the end wins.\n");
	printf("\tHere are the card rankings from highest to lowest\n");
	printf("\t| Straight | Five cards of consecutive face values\n");
	printf("\t|  flush  | Five cards of the same suit\n");
	printf("\t| Four of a Kind | Four matching face values\n");
	printf("\t| Three of a kind | Three matching face values\n");
	printf("\t| Two pairs| Two matching sets of face values\n");
	printf("\t| a pair | One matching set of face values\n");
	system("pause");
	system("cls");
}


/*
	Name: Douglas Takda
	Function: rest_deck
	date: 12/1/2021
	Input parameters: deck[][13]
	Returns: Void
	Description: The function resets the deck every time it is called
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the array in the parameter
	Postconditions: The function resets the card deck
*/
void reset_deck(int deck[][13]) {
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 12; j++) {
			deck[i][j] = 0;
		}
	}
}


/*
	Name: Douglas Takda
	Function: shuffle
	date: 12/1/2021
	Input parameters: Deck[][13]
	Returns: Void
	Description: The function shuffles the deck my randomly placing number of 1-52 in
				a 4 X 13 size array which represents in which order what cards
				will be drawn in the order from 1-52. the indexes of this 2D array
				represnts the suit and face value
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the array in the parameter
	Postconditions: The function shuffles the card deck
*/
void shuffle(int Deck[][13])
{
	reset_deck(Deck);
	int row = 0;
	int column = 0;
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (Deck[row][column] != 0);

		/* place card number in chosen slot of deck */
		Deck[row][column] = card;
	}
}

/* deal cards in deck */
/*
	Name: Douglas Takda
	Function: deal
	date: 12/1/2021
	Input parameters: const int wDeck[][13], int deal_num,int *cards, Hand *player_hand
	Returns: void
	Description: The function deals cards to the hand that is passed through the parameter
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function deals cards from the card deck
*/
void deal(const int wDeck[][13], int deal_num, int* cards, Hand* player_hand)
{
	int dealt = 0;
	int row = 0;
	int column = 0;
	int temp = *cards;

	/* deal each of the 52 cards */
	for (; dealt + temp < deal_num + temp; (*cards)++)
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				if (wDeck[row][column] == *cards)
				{
					dealt++;
					player_hand->hand[*cards - temp].index_face = column;
					player_hand->hand[*cards - temp].index_suit = row;
				}
			}
		}
	}
}


/*
	Name: Douglas Takda
	Function: redeal
	date: 12/1/2021
	Input parameters: const int wDeck[][13], int card_num, int* cards, Hand* player_hand
	Returns: void
	Description: The function deals one card to the hand that is passed through the parameter
				and replaces the card index that is passed through the parameter
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function deals one card from the card deck into a players hand
*/
void redeal(const int wDeck[][13], int card_num, int* cards, Hand* player_hand) {
	int row = 0;
	int column = 0;
	int temp = *cards;

	/* deal each of the 52 cards */
	for (int i = 0; i < 1; (*cards)++, i++)
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				if (wDeck[row][column] == *cards)
				{
					player_hand->hand[card_num].index_face = column;
					player_hand->hand[card_num].index_suit = row;
				}
			}
		}
	}
}


/*
	Name: Douglas Takda
	Function: print_hand
	date: 12/1/2021
	Input parameters: const char* wFace[], const char* wSuit[], Hand player_hand
	Returns: void
	Description: The function prints the hand that is passed through as a parameter
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function prints the hand that is passed in the parameter
*/
void print_hand(const char* wFace[], const char* wSuit[], Hand player_hand)
{
	int card = 0;   /* card counter*/

	/* prints the five cards of the players cards */
	for (card = 0; card <= 4; card++) {
		printf("%5s of %-8s%c", wFace[player_hand.hand[card].index_face],
			wSuit[player_hand.hand[card].index_suit],
			card % 2 == 0 ? '\n\t' : '\t');
	}
}


/*
	Name: Douglas Takda
	Function: check_frequency
	date: 12/1/2021
	Input parameters: int p_suit_freq[], int p_val_freq[], Hand p_hand, int card_index[]
	Returns: void
	Description: This function untilizes a frequency array and counts the number of
				types of cards there are in the hand that is passed through the parameter
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function fills the frequency array for future calculations
*/
void check_frequency(int p_suit_freq[], int p_val_freq[], Hand p_hand, int card_index[]) {
	for (int i = 0; i < 13; i++) {
		p_val_freq[i] = 0;
	}
	for (int i = 0; i < 4; i++) {
		p_suit_freq[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		card_index[p_hand.hand[i].index_face] = i;
		p_val_freq[p_hand.hand[i].index_face]++;
		p_suit_freq[p_hand.hand[i].index_suit]++;
	}
}


/*
	Name: Douglas Takda
	Function: card_change
	date: 12/1/2021
	Input parameters: const int wDeck[][13], int *cards, Hand *player_hand,
	const char* wFace[], const char* wSuit[]
	Returns: void
	Description: This function prompts the user to enter y or n to determine
				if they would like to swap cards. The user may swap up to three
				cards. If they do want to swap cards another function is called
				and swaps the card they are asking to discard
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function replaces up to three cards that the player would like
					to replace
*/
void card_change(const int wDeck[][13], int* cards, Hand* player_hand,
	const char* wFace[], const char* wSuit[]) {
	int card = 0, temp1 = 0, counter = 0;
	char temp = '\0';
	printf("\n\tRemeber you can only discard and draw three cards\n\n");
	for (card = 0; card <= 4; card++) {
		temp = '\0';
		temp1 = 1;
		printf("%5s of %-8s%c", wFace[player_hand->hand[card].index_face],
			wSuit[player_hand->hand[card].index_suit], card % 2 == 0 ? '\n\t' : '\n\t');

		while (temp != 'y' && temp != 'Y' && temp != 'n' && temp != 'N') {
			if (temp1 != 1) {
				printf("\nYou have input a invalid option please enter y or n");
			}
			if (counter >= 3) {
				break;
			}

			printf("\nWould you like to replace this card? ");//
			scanf(" %c", &temp);
			temp1++;
		}
		if ((temp == 'y' && counter < 3) || (temp == 'Y' && counter < 3)) {
			redeal(wDeck, card, cards, player_hand);
			counter++;
		}
	}
}


/*
	Name: Douglas Takda
	Function: dealer_card_change
	date: 12/1/2021
	Input parameters: int best_combo, Hand *player_hand, const int wDeck[][13],
	int *cards, int card_index[], int freq[]
	Returns: void
	Description: This function uses all the information given through the parameters to
				determine how many and what kind of cards they would like to replace
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function replaces up to three cards that the computer would like
					to replace
*/
void dealer_card_change(int best_combo, Hand* player_hand, const int wDeck[][13],
	int* cards, int card_index[], int freq[]) {
	switch (best_combo) {
	case 0:// Straight - 12345
		printf("\n\tThe dealer does not change any of his cards\n");
		break;
	case 1://Flush - Same suit
		printf("\n\tThe dealer does not change any of his cards\n");
		break;
	case 2://Four of a kind/ discard one
		for (int i = 0; i < 13; i++) {
			if (freq[i] == 1) {
				redeal(wDeck, card_index[i], cards, player_hand);
			}
		}
		printf("\n\tThe dealer discards and draws one card\n");
		break;
	case 3://Three of a kind
		for (int i = 0; i < 13; i++) {
			if (freq[i] == 1 || freq[i] == 2) {
				redeal(wDeck, card_index[i], cards, player_hand);
			}
		}
		printf("\n\tThe dealer discards and draws two cards\n");
		break;
	case 4:// Two pair
		for (int i = 0; i < 13; i++) {
			if (freq[i] == 1) {
				redeal(wDeck, card_index[i], cards, player_hand);
			}
		}
		printf("\n\tThe dealer discards and draws one card\n");
		break;
	case 5:// One pair
		for (int i = 0; i < 13; i++) {
			if (freq[i] == 1) {
				redeal(wDeck, card_index[i], cards, player_hand);
			}
		}
		printf("\n\tThe dealer discards and draws three cards\n");
		break;
	case 6://No combination
		redeal(wDeck, 0, cards, player_hand);
		redeal(wDeck, 1, cards, player_hand);
		redeal(wDeck, 2, cards, player_hand);
		printf("\n\tThe dealer discards and draws three cards");
		break;
	}
}


/*
	Name: Douglas Takda
	Function: is_pair
	date: 12/1/2021
	Input parameters: face_freq[]
	Returns: int
	Description: This uses the frequency array that was filled from prior functions
				and determines if the types of combinations that is in the hand that
				is passed through as an argument is a pair or not
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function returns 1 if it is a pair and if not return 0
*/
int is_pair(int face_freq[]) {
	for (int i = 0; i <= 12; i++) {
		if (face_freq[i] >= 2) {
			return 1;
		}
	}
	return 0;
}


/*
	Name: Douglas Takda
	Function: is_two_pair
	date: 12/1/2021
	Input parameters: face_freq[]
	Returns: int
	Description: This uses the frequency array that was filled from prior functions
				and determines if the types of combinations that is in the hand that
				is passed through as an argument to see if there are two pairs
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function returns 1 if there are two pairs and if not return 0
*/
int is_two_pair(int face_freq[]) {
	int counter = 0;
	for (int i = 0; i <= 12; i++) {
		if (face_freq[i] >= 2) {
			counter++;
		}
	}
	if (counter >= 2) {
		return 1;
	}
	else { return 0; }
}


/*
	Name: Douglas Takda
	Function: three_of_a_kind
	date: 12/1/2021
	Input parameters: face_freq[]
	Returns: int
	Description: This uses the frequency array that was filled from prior functions
				and determines if the types of combinations that is in the hand that
				is passed through as an argument to see if there is a three of a kind
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function returns 1 if there is a three of a kind and if not
					returns 0
*/
int is_three_of_a_kind(int face_freq[]) {
	for (int i = 0; i <= 12; i++) {
		if (face_freq[i] >= 3) {
			return 1;
		}
	}
	return 0;
}


/*
	Name: Douglas Takda
	Function: four_of_a_kind
	date: 12/1/2021
	Input parameters: face_freq[]
	Returns: int
	Description: This uses the frequency array that was filled from prior functions
				and determines if the types of combinations that is in the hand that
				is passed through as an argument to see if there is a four of a kind
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function returns 1 if there is a four of a kind and if not
					returns 0
*/
int is_four_of_a_kind(int face_freq[]) {
	for (int i = 0; i <= 12; i++) {
		if (face_freq[i] >= 4) {
			return 1;
		}
	}
	return 0;
}


/*
	Name: Douglas Takda
	Function: is_flush
	date: 12/1/2021
	Input parameters: suit_freq[]
	Returns: int
	Description: This uses the frequency array that was filled from prior functions
				and determines if the types of combinations that is in the hand that
				is passed through as an argument to see if there is a flush. This time
				the frequency array that is being used is the suit frequency array
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function returns 1 if there is a flush and if not it returns 0
*/
int is_flush(int suit_freq[]) {
	for (int i = 0; i < 5; i++) {
		if (suit_freq[i] == 5) {
			return 1;
		}
	}
	return 0;
}


/*
	Name: Douglas Takda
	Function: is_straight
	date: 12/1/2021
	Input parameters: face_freq[]
	Returns: int
	Description: This uses the frequency array that was filled from prior functions
				and determines if the types of combinations that is in the hand that
				is passed through as an argument to see if there is a straight
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function returns 1 if there is a straight and if not returns 0
*/
int is_straight(int face_freq[]) {
	for (int i = 0; i <= 7; i++) {
		if (face_freq[i] == 1 && face_freq[i + 1] == 1 && face_freq[i + 2] == 1
			&& face_freq[i + 3] == 1 && face_freq[i + 4] == 1) {
			return 1;

		}
	}
	return 0;
}

/*
	Name: Douglas Takda
	Function: quality_hand
	date: 12/1/2021
	Input parameters: int face_freq[], int suit_freq[],int p_combo[]
	Returns: int
	Description: This function calls all of the functions that check for pairs,
				Two pairs, three of a kind, four of a kind, flush, and straight
				These functions all return 1 or 0 and that determines if the hand
				that is passed thorough the function has these combinations or not
				these 1 or 0 are then checked in order of what kind of combinations
				take precedence over other combinations the combination of highest
				precedence is returned
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function the combination that is of highest precedence
*/
int quality_hand(int face_freq[], int suit_freq[], int p_combo[]) {

	p_combo[0] = is_straight(face_freq);
	p_combo[1] = is_flush(suit_freq);
	p_combo[2] = is_four_of_a_kind(face_freq);
	p_combo[3] = is_three_of_a_kind(face_freq);
	p_combo[4] = is_two_pair(face_freq);
	p_combo[5] = is_pair(face_freq);
	p_combo[6] = 1;

	for (int i = 0; i <= 6; i++) {
		if (p_combo[i] == 1) {
			return i;
		}
	}
}


/*
	Name: Douglas Takda
	Function: order_cards
	date: 12/1/2021
	Input parameters: player_hand
	Returns: void
	Description: This function orders the hand that is passed through the parameter
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function indrectly returns the order of the argument hand from
					lowest to highest
*/
void order_cards(Hand* player_hand) {
	int temp_face = 0, temp_suit = 0, passes = 0, index = 0;
	for (; passes < 5; ++passes) {
		for (index = 0; index < 5 - passes - 1; ++index) {
			if (player_hand->hand[index].index_face > player_hand->hand[index + 1].index_face)
			{
				temp_face = player_hand->hand[index].index_face;
				temp_suit = player_hand->hand[index].index_suit;

				player_hand->hand[index].index_face = player_hand->hand[index + 1].index_face;
				player_hand->hand[index].index_suit = player_hand->hand[index + 1].index_suit;

				player_hand->hand[index + 1].index_face = temp_face;
				player_hand->hand[index + 1].index_suit = temp_suit;
			}
		}
	}
}


/*
	Name: Douglas Takda
	Function: determine_winner
	date: 12/1/2021
	Input parameters: p1_score, p2_score
	Returns: void
	Description: This function prints and determines who was the winner in this game
				by comparing the combinations that the two players had
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function prints who the winner was
*/
void determine_winner(int p1_score, int p2_score) {
	if (p1_score < p2_score) {
		printf("\nCongrats! You won!\n");
	}
	else
		if (p1_score > p2_score) {
			printf("\nDarn you lost\n");
		}
		else
			if (p1_score == p2_score) {

				printf("\nIt was a tie\n");
			}
}