
/*Six rows; seven columns

Use struct to build board //Board is defined as a 2d matrix
There is a black and a red token

Struct is made up of struct cells occupied or not occupied; rows; columns

*/

#include "functions.h"

int main(void)
{
	Board the_board = { {{{NONE, {0, 0},NO}}} };
	Token_color p1_tok = BLACK;
	Token_color p2_tok = RED;

	//printf("sizeof struct board: %d\n", sizeof(Board));

	init_board(&the_board);
	// although we're not changing the board
	// in print_board, we're passing-by-pointer
	// so that a lot less memory is copied. we
	// try to preserve memory when we can.

	printf("\tHere is the board you will be playing\n");
	printf("\tPlayer 1 will have black tokens represented as the the 'b' chracter\n");
	printf("\tPlayer 2 will have red tokens represented as the 'r' chracter\n");
	print_board(&the_board);
	system("pause");
	system("cls");
	int game_over = 0, temp = 0, column_counter[MAX_COLS] = { 5,5,5,5,5,5,5 };
	while (game_over == 0) {
		if (check_tie(&the_board) == 1) {
			print_board(&the_board);
			printf("\n\tAll of the cells have been filled. It is a tie.\n");
			break;
		}
		printf("\tIt is player 1's Turn\n");
		printf("\tEnter the column where you would like to place your token!\n");
		print_board(&the_board);
		scanf("%d", &temp);
		system("cls");
		while (column_counter[temp] < 0) {
			printf("\tThat column is filled please choose a different column\n");
			print_board(&the_board);
			scanf("%d", &temp);

		}
		place_token(&(the_board.game_board[column_counter[temp]--][temp]), p1_tok);
		if (check_logic(&the_board, BLACK) == 1) {
			print_board(&the_board);
			printf("\n\tCongrats Player 1 Won!\n");
			game_over = 1;
			break;
		}
		if (check_tie(&the_board) == 1) {
			print_board(&the_board);
			printf("\n\tAll of the cells have been filled. It is a tie.\n");
			break;
		}
		printf("\tIt is player 2's Turn\n");
		printf("\tEnter the column where you would like to place your token!\n");
		print_board(&the_board);
		scanf("%d", &temp);
		system("cls");
		while (column_counter[temp] < 0) {
			printf("\tThat column is filled please choose a different column\n");
			print_board(&the_board);
			scanf("%d", &temp);
		}
		place_token(&(the_board.game_board[column_counter[temp]--][temp]), p2_tok);
		if (check_logic(&the_board, RED) == 1) {
			print_board(&the_board);
			printf("\n\tCongrats Player 2 Won!\n");
			game_over = 1;
			break;
		}
	}

	return 0;
}