#define _CRT_SECURE_NO_WARNINGS
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define GAME_RULES 1
#define PLAY_GAME 2
#define EXIT 3

typedef struct card {
	int index_face;
	int index_suit;
}Card;

typedef struct hand {
	Card hand[5];

}Hand;


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
int menu(void);


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
void game_rules(void);


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
void reset_deck(int deck[][13]);


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
void shuffle(int wDeck[][13]);


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
void deal(const int wDeck[][13], int deal_num, int* cards, Hand* player_hand);


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
void redeal(const int wDeck[][13], int card_num, int* cards, Hand* player_hand);


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
void print_hand(const char* wFace[], const char* wSuit[], Hand player_hand);


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
void check_frequency(int p_suit[], int p_val[], Hand p_hand, int card_index[]);


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
	const char* wFace[], const char* wSuit[]);


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
void dealer_card_change(int best_combo, Hand* player_hand, const int Deck[][13], int* cards, int card_index[], int freq[]);

/*
	Name: Douglas Takda
	Function: is_pair
	date: 12/1/2021
	Input parameters: face_freq[]
	Returns: int
	Description: This usues the frequency array that was filled from prior functions
				and determines if the types of combinations that is in the hand that
				is passed through as an argument is a pair or not
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function returns 1 if it is a pair and if not return 0
*/
int is_pair(int face_freq[]);


/*
	Name: Douglas Takda
	Function: is_two_pair
	date: 12/1/2021
	Input parameters: face_freq[]
	Returns: int
	Description: This usues the frequency array that was filled from prior functions
				and determines if the types of combinations that is in the hand that
				is passed through as an argument to see if there are two pairs
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function returns 1 if there are two pairs and if not return 0
*/
int is_two_pair(int face_freq[]);


/*
	Name: Douglas Takda
	Function: three_of_a_kind
	date: 12/1/2021
	Input parameters: face_freq[]
	Returns: int
	Description: This usues the frequency array that was filled from prior functions
				and determines if the types of combinations that is in the hand that
				is passed through as an argument to see if there is a three of a kind
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function returns 1 if there is a three of a kind and if not
					returns 0
*/
int is_three_of_a_kind(int face_freq[]);


/*
	Name: Douglas Takda
	Function: four_of_a_kind
	date: 12/1/2021
	Input parameters: face_freq[]
	Returns: int
	Description: This usues the frequency array that was filled from prior functions
				and determines if the types of combinations that is in the hand that
				is passed through as an argument to see if there is a four of a kind
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function returns 1 if there is a four of a kind and if not
					returns 0
*/
int is_four_of_a_kind(int face_freq[]);


/*
	Name: Douglas Takda
	Function: is_flush
	date: 12/1/2021
	Input parameters: suit_freq[]
	Returns: int
	Description: This usues the frequency array that was filled from prior functions
				and determines if the types of combinations that is in the hand that
				is passed through as an argument to see if there is a flush. This time
				the frequency array that is being used is the suit frequency array
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function returns 1 if there is a flush and if not it returns 0
*/
int is_flush(int suit_freq[]);


/*
	Name: Douglas Takda
	Function: is_straight
	date: 12/1/2021
	Input parameters: face_freq[]
	Returns: int
	Description: This usues the frequency array that was filled from prior functions
				and determines if the types of combinations that is in the hand that
				is passed through as an argument to see if there is a straight
	Preconditions: The preconditions that are needed are the start of the program and
					proper intialization of the variables in the parameter
	Postconditions: The function returns 1 if there is a straight and if not returns 0
*/
int is_straight(int face_freq[]);


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
int quality_hand(int face_freq[], int suit_freq[], int p_combo[]);


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
void order_cards(Hand* player_hand);

void determine_winner(int p1_score, int p2_score);

#endif