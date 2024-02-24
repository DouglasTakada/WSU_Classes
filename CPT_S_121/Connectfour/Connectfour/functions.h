#ifndef CONNECTFOUR
#define CONNECTFOUR
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 6
#define MAX_COLS 7

typedef enum token_color
{
	NONE, RED, BLACK
} Token_color;

typedef enum occupied
{
	NO, YES
}Occupied;

typedef struct coordinate
{
	int row;
	int col;
}Coordinate;

typedef struct cell
{
	Token_color token;
	Coordinate position;
	Occupied yes_no;
}Cell;

typedef struct board
{
	Cell game_board[MAX_ROWS][MAX_COLS];
	int num_rows;
	int num_cols;
}Board;


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
void init_board(Board* the_board_ptr);
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
void print_board(const Board* the_board_ptr);


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
void place_token(Cell* cell_ptr, Token_color player_token);

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
int check_logic(const Board* the_board_ptr, int player);


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
int check_tie(const Board* the_board_ptr);

#endif
