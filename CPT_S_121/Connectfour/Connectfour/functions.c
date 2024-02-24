#include "functions.h"

/*
	Name: DT
	Function: init_board(Board* the_board_ptr)
	date: 12/17/2021
	Input parameters: Board* the_board_ptr
	Returns: Nothing
	Description: This function initializes the board so each cell is considered
					to have no token and to be empty
	Preconditions: The preconditions that are needed are the start of the program
	Postconditions: The connect 4 board is initialized
*/
void init_board(Board* the_board_ptr)
{
	int row_index = 0, col_index = 0;

	// note: (*). is equivalent to ->
	// these operators only work with pointers to structs
	(*the_board_ptr).num_rows = MAX_ROWS;
	the_board_ptr->num_cols = MAX_COLS;

	for (; row_index < the_board_ptr->num_rows;
		++row_index) // the row in the board
	{
		for (col_index = 0;
			col_index < the_board_ptr->num_cols;
			++col_index) // the col in the board
		{
			// set the cell in the board
			// empty cell - no token color
			the_board_ptr->game_board[row_index][col_index].token = NONE;
			// no token in cell
			the_board_ptr->game_board[row_index][col_index].yes_no = NO;
			// what row is this cell we're initializing in?
			the_board_ptr->game_board[row_index][col_index].position.row = row_index;
			// what row is this cell we're initializing in?
			the_board_ptr->game_board[row_index][col_index].position.col = col_index;
		}
	}
}


// we're passing-by-pointer
// so that a lot less memory is copied. we
// try to preserve memory when we can.
/*
	Name: DT
	Function: print_board(const Board* the_board_ptr)
	date: 12/17/2021
	Input parameters: const Board* the_board_ptr
	Returns: Nothing
	Description: This function prints the connect 4 board and the numbered columns about it
	Preconditions: The preconditions that are needed are the start of the program
	Postconditions: The connect 4 board is printed
*/
void print_board(const Board* the_board_ptr)
{
	int row_index = 0, col_index = 0;

	printf("0 1 2 3 4 5 6\n"); // column headings

	for (; row_index < the_board_ptr->num_rows;
		++row_index) // the row in the board

	{
		for (col_index = 0;
			col_index < the_board_ptr->num_cols;
			++col_index) // the col in the board
		{
			// let's print a dash for an empty cell in the
			// board
			if (the_board_ptr->game_board[row_index][col_index].yes_no == NO)
			{
				printf("%c ", '-'); // coul also use putchar () here
			}
			else
			{
				// please consider removing the if-else and
				// creating a single switch () statement with 3 cases!
				switch (the_board_ptr->game_board[row_index][col_index].token)
				{
				case RED: printf("%c ", 'r');
					break;
				case BLACK: printf("%c ", 'b');
					break;
				}
			}
		}
		putchar('\n');
	}
}


/*Going to need a counter for every column that always increments everytime that column is used
Because using the same counter will not allow to use the row in any other column*/
/*
	Name: DT
	Function: place_token(Cell* cell_ptr, Token_color player_token)
	date: 12/17/2021
	Input parameters: Cell* cell_ptr, Token_color player_token
	Returns: Nothing
	Description: This function places the token in the columns that the user input
	Preconditions: The preconditions that are needed are the start of the program
	Postconditions: The users token is placed in the column where the user requested
*/
void place_token(Cell* cell_ptr, Token_color player_token)
{
	(*cell_ptr).token = player_token;
	cell_ptr->yes_no = YES;
}


/*
	Name: DT
	Function: check_logic(const Board* the_board_ptr, int player)
	date: 12/17/2021
	Input parameters: const Board* the_board_ptr, int player
	Returns: integer depending on if there is a four in a row vertically, horizontally or diagonally
	Description: This function checks the board to see if either players have won the game
				 by checking for diagonal, horizontal, and vertical matches
	Preconditions: The preconditions that are needed are the start of the program
	Postconditions: If a user has a connect four a 1 is returned, otherwise 0 is returned
*/
int check_logic(const Board* the_board_ptr, int player) {
	int horizontal = 0, verticle = 0, diagonal = 0;
	if (player == BLACK) {//check for black positions 
		for (int i = 5; i > 0; i--) {//iterate through all row
			for (int j = 0; j < 3; j++) {//Iterate through first half columns
				if (the_board_ptr->game_board[i][j].token == BLACK) {// check all horizontal combos
					for (int k = 0; k < 4; k++) {
						if (the_board_ptr->game_board[i][j + k].token == BLACK) {
							horizontal++;
						}
					}
					if (horizontal >= 4) return 1;
					horizontal = 0;
				}
			}
		}
		for (int i = 5; i >= 3; i--) {//iterate through 
			for (int j = 0; j < 6; j++) {//Iterate through all
				if (the_board_ptr->game_board[i][j].token == BLACK) {// check all Verticle combos
					for (int k = 0; k < 4; k++) {
						if (the_board_ptr->game_board[i - k][j].token == BLACK) {
							verticle++;
						}
					}
					if (verticle >= 4) return 1;
					verticle = 0;
				}
			}
			for (int j = 0; j <= 3; j++) {//Iterate through first half columns
				if (the_board_ptr->game_board[i][j].token == BLACK) {// check half diagonal combos
					for (int k = 0; k < 4; k++) {
						if (the_board_ptr->game_board[i - k][j + k].token == BLACK) {
							diagonal++;
						}
					}
					if (diagonal >= 4) return 1;
					diagonal = 0;
				}
			}
			for (int j = 6; j >= 3; j--) {//Iterate through first half columns
				if (the_board_ptr->game_board[i][j].token == BLACK) {// check rest diagonal combos
					for (int k = 0; k < 4; k++) {
						if (the_board_ptr->game_board[i - k][j - k].token == BLACK) {
							diagonal++;
						}
					}
					if (diagonal >= 4) return 1;
					diagonal = 0;
				}
			}

		}
	} else {
		for (int i = 5; i > 0; i--) {//iterate through all row
			for (int j = 0; j < 3; j++) {//Iterate through first half columns
				if (the_board_ptr->game_board[i][j].token == RED){// check all horizontal combos
					for (int k = 0; k < 4; k++) {
						if (the_board_ptr->game_board[i][j + k].token == RED) {
							horizontal++;
						}
					}
					if (horizontal >= 4) return 1;
					horizontal = 0;
				}
			}
		}
		for (int i = 5; i >= 3; i--) {//iterate through 
			for (int j = 0; j < 6; j++) {//Iterate through all
				if (the_board_ptr->game_board[i][j].token == RED) {// check all Verticle combos
					for (int k = 0; k < 4; k++) {
						if (the_board_ptr->game_board[i - k][j].token == RED) {
							verticle++;
						}
					}
					if (verticle >= 4) return 1;
					verticle = 0;
				}
			}
			for (int j = 0; j <= 3; j++) {//Iterate through first half columns
				if (the_board_ptr->game_board[i][j].token == RED) {// check half diagonal combos
					for (int k = 0; k < 4; k++) {
						if (the_board_ptr->game_board[i - k][j + k].token == RED) {
							diagonal++;
						}
					}
					if (diagonal >= 4) return 1;
					diagonal = 0;
				}
			}
			for (int j = 6; j >= 3; j--) {//Iterate through first half columns
				if (the_board_ptr->game_board[i][j].token == RED) {// check rest diagonal combos
					for (int k = 0; k < 4; k++) {
						if (the_board_ptr->game_board[i - k][j - k].token == RED) {
							diagonal++;
						}
					}
					if (diagonal >= 4) return 1;
					diagonal = 0;
				}
			}

		}
	}

	return 0;

}

/*
	Name: DT
	Function: check_tie(const Board* the_board_ptr)
	date: 12/17/2021
	Input parameters: const Board* the_board_ptr
	Returns: returns 1 if all cells are filled, otherwise returns a 0
	Description: This function checks the board to see if all cells on the connect 4 board has
					been exausted or not. If they are, then the game ends in a draw and the
					function returns a 1. Otherwise the function returns a 0
	Preconditions: The preconditions that are needed are the start of the program
	Postconditions: a 1 or 0 is returned depending on if all of the cells are occupied
*/
int check_tie(const Board* the_board_ptr) {
	int counter = 0;
	for (int i = 0; i < the_board_ptr->num_rows ; i++) {
		for (int j = 0; j < the_board_ptr->num_cols ; j++) {
			if (the_board_ptr->game_board[i][j].yes_no ==YES) {
				counter++;
			}
		}
	}
	if (counter == 42) return 1;
	else return 0; 
}