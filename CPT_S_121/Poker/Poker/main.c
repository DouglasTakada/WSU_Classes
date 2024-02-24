/*
* Author: Douglas Takada
* Date: December 1st 2021
* Description:		This program enables the user to play five card
*					draw poker with the computer This program uses two
*					demensional arrays and strings to keep track of
*					various types of cards in the deck. This program also
*					uses structs for the user and the computers hand.
*					This program prompts the user to keep playing until
*					they would like to quit
*/

#include "functions.h"

int main(void) {
	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five",
		"Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

	int deck[4][13] = { 0 }, cards = 1, menuv = 0, p1_suit[4] = { 0 }, p1_val[13] = { 0 },
		p2_suit[4] = { 0 }, p2_val[13] = { 0 }, p1_combos[7] = { 0 }, p2_combos[7] = { 0 },
		p2_best = 0, p1_best = 0, discard[3] = { 0 }, p1_card_index[13] = { 0 }, p2_card_index[13] = { 0 };

	srand((unsigned)time(NULL)); /* seed random-number generator */
	Hand p1_hand = { 0 }, p2_hand = { 0 };
	while (menuv != 3) {
		menuv = menu();
		switch (menuv) {
		case GAME_RULES:
			game_rules();
			break;
		case PLAY_GAME://Play Game Here
			//Round 1:
			system("cls");
			cards = 1;
			shuffle(deck);
			deal(deck, 5, &cards, &p1_hand);// Deal cards to player 1
			deal(deck, 5, &cards, &p2_hand);// Deal cards to player 2
			order_cards(&p1_hand);
			order_cards(&p2_hand);


			printf("\tYour Hand:\n");
			print_hand(face, suit, p1_hand);

			/*Change card for p1*/
			card_change(deck, &cards, &p1_hand, face, suit);
			order_cards(&p1_hand);
			system("cls");

			/*Change card for p2*/
			check_frequency(p2_suit, p2_val, p2_hand, p2_card_index);
			p2_best = quality_hand(p2_val, p2_suit, p2_combos);
			dealer_card_change(p2_best, &p2_hand, deck, &cards, p2_card_index, p2_val);
			order_cards(&p2_hand);


			/*End of round 1*/
			printf("\n\tHere are your new cards\n");
			print_hand(face, suit, p1_hand);
			system("pause");


			//Round 2:

			system("cls");
			printf("\n\tThis is the last round until your cards will be evaluated\n");
			printf("\n\tYour Hand\n");
			print_hand(face, suit, p1_hand);

			/*Change cards for p1*/
			card_change(deck, &cards, &p1_hand, face, suit);
			order_cards(&p1_hand);

			/*Change cards for p2*/
			order_cards(&p2_hand);
			check_frequency(p2_suit, p2_val, p2_hand, p2_card_index);
			p2_best = quality_hand(p2_val, p2_suit, p2_combos, p2_card_index);
			dealer_card_change(p2_best, &p2_hand, deck, &cards, p2_card_index, p2_val);
			order_cards(&p2_hand);

			/*Check for frequency and compare who had the better combination*/
			check_frequency(p1_suit, p1_val, p1_hand, p1_card_index);
			check_frequency(p2_suit, p2_val, p2_hand, p2_card_index);
			p2_best = quality_hand(p2_val, p2_suit, p2_combos, p2_card_index);
			p1_best = quality_hand(p1_val, p1_suit, p1_combos, p1_card_index);

			/*End of round 2*/
			system("cls");
			printf("\n\tHere are your new cards\n");
			print_hand(face, suit, p1_hand);
			printf("\n\tHere was your opponents Hand:\n");
			print_hand(face, suit, p2_hand);


			/*Print who won*/
			determine_winner(p1_best, p2_best);
			system("pause");
			system("cls");

		case EXIT:
			break;
		}
	}
	system("cls");
	printf("\tThanks for playing!");
	return 0;
}