/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:35:05 by gasselin          #+#    #+#             */
/*   Updated: 2022/01/19 11:25:36 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCED 2
#define CUSTOM 3
#define MAXSIDE 50
#define MAXMINES 99
#define MOVESIZE 2500 // (25 * 25 - 99)

int SIDE ; // side length of the board
int MINES ; // number of mines on the board
int FLAGS;

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not
bool isValid(int row, int col)
{
	// Returns true if row number and column number
	// is in range
	return (row >= 0) && (row < SIDE) &&
		(col >= 0) && (col < SIDE);
}

// A Utility Function to check whether given cell (row, col)
// has a mine or not.
bool isMine (int row, int col, char board[][MAXSIDE])
{
	if (board[row][col] == '*')
		return (true);
	else
		return (false);
}

// A Function to get the user's move and print it
// All the moves are assumed to be distinct and valid.
void makeMove (int *x, int *y, int moves[][2], int currentMoveIndex)
{
	*x = moves[currentMoveIndex][0];
	*y = moves[currentMoveIndex][1];

	printf ("\nMy move is (%d, %d)\n", *x, *y);

	/*
	// The above moves are pre-defined
	// If you want to make your own move
	// then uncomment this section and comment
	// the above section

	scanf("%d %d", x, y);
	*/

	return;
}

// A Function to randomly assign moves
void assignMoves (int moves[][2], int movesLeft)
{
	bool mark[MAXSIDE*MAXSIDE];

	memset(mark, false, sizeof(mark));

	// Continue until all moves are assigned.
	for (int i=0; i<movesLeft; )
	{
		int random = rand() % (SIDE*SIDE);
		int x = random / SIDE;
		int y = random % SIDE;

		// Add the mine if no mine is placed at this
		// position on the board
		if (mark[random] == false)
		{
			// Row Index of the Mine
			moves[i][0]= x;
			// Column Index of the Mine
			moves[i][1] = y;

			mark[random] = true;
			i++;
		}
	}

	return;
}

// A Function to print the current gameplay board
void printBoard(char myBoard[][MAXSIDE])
{
	int i,j;

	printf (" ");

	for (i=0; i<SIDE; i++)
		printf ("%d ", i);

	printf ("\n\n");

	for (i=0; i<SIDE; i++)
	{
		printf ("%d ", i);

		for (j=0; j<SIDE; j++)
			printf ("%c ", myBoard[i][j]);
		printf ("\n");
	}
	return;
}

// A Function to count the number of
// mines in the adjacent cells
int countAdjacentMines(int row ,int col ,int mines[][2], char realBoard[][MAXSIDE])
{

	int i;
	int count = 0;

	/*
		Count all the mines in the 8 adjacent
		cells

			N.W N N.E
			\ | /
			\ | /
			W----Cell----E
				/ | \
			/ | \
			S.W S S.E

		Cell-->Current Cell (row, col)
		N --> North	 (row-1, col)
		S --> South	 (row+1, col)
		E --> East		 (row, col+1)
		W --> West		 (row, col-1)
		N.E--> North-East (row-1, col+1)
		N.W--> North-West (row-1, col-1)
		S.E--> South-East (row+1, col+1)
		S.W--> South-West (row+1, col-1)
	*/

	//----------- 1st Neighbour (North) ------------

		// Only process this cell if this is a valid one
		if (isValid (row-1, col) == true)
		{
			if (isMine (row-1, col, realBoard) == true)
			count++;
		}

	//----------- 2nd Neighbour (South) ------------

		// Only process this cell if this is a valid one
		if (isValid (row+1, col) == true)
		{
			if (isMine (row+1, col, realBoard) == true)
			count++;
		}

	//----------- 3rd Neighbour (East) ------------

		// Only process this cell if this is a valid one
		if (isValid (row, col+1) == true)
		{
			if (isMine (row, col+1, realBoard) == true)
			count++;
		}

	//----------- 4th Neighbour (West) ------------

		// Only process this cell if this is a valid one
		if (isValid (row, col-1) == true)
		{
			if (isMine (row, col-1, realBoard) == true)
			count++;
		}

	//----------- 5th Neighbour (North-East) ------------

		// Only process this cell if this is a valid one
		if (isValid (row-1, col+1) == true)
		{
			if (isMine (row-1, col+1, realBoard) == true)
			count++;
		}

	//----------- 6th Neighbour (North-West) ------------

		// Only process this cell if this is a valid one
		if (isValid (row-1, col-1) == true)
		{
			if (isMine (row-1, col-1, realBoard) == true)
			count++;
		}

	//----------- 7th Neighbour (South-East) ------------

		// Only process this cell if this is a valid one
		if (isValid (row+1, col+1) == true)
		{
			if (isMine (row+1, col+1, realBoard) == true)
			count++;
		}

	//----------- 8th Neighbour (South-West) ------------

		// Only process this cell if this is a valid one
		if (isValid (row+1, col-1) == true)
		{
			if (isMine (row+1, col-1, realBoard) == true)
			count++;
		}

	return (count);
}

// A Recursive Function to play the Minesweeper Game
bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE],
			int mines[][2], int row, int col, int *movesLeft)
{

	// Base Case of Recursion
	if (myBoard[row][col]!='-')
		return (false);

	int i, j;

	// You opened a mine
	// You are going to lose
	if (realBoard[row][col] == '*')
	{
		myBoard[row][col]='*';

		for (i=0; i<MINES; i++)
			myBoard[mines[i][0]][mines[i][1]]='*';

		printBoard (myBoard);
		printf ("\nYou lost!\n");
		return (true) ;
	}

	else
	{

		// Calculate the number of adjacent mines and put it
		// on the board.
		int count = countAdjacentMines(row, col, mines, realBoard);
		(*movesLeft)--;

		myBoard[row][col] = count + '0';

		if (!count)
		{
			/*
			Recur for all 8 adjacent cells

				N.W N N.E
				\ | /
					\ | /
				W----Cell----E
					/ | \
				/ | \
				S.W S S.E

			Cell-->Current Cell (row, col)
			N --> North	 (row-1, col)
			S --> South	 (row+1, col)
			E --> East		 (row, col+1)
			W --> West		 (row, col-1)
			N.E--> North-East (row-1, col+1)
			N.W--> North-West (row-1, col-1)
			S.E--> South-East (row+1, col+1)
			S.W--> South-West (row+1, col-1)
			*/

				//----------- 1st Neighbour (North) ------------

			// Only process this cell if this is a valid one
			if (isValid (row-1, col) == true)
			{
				if (isMine (row-1, col, realBoard) == false)
				playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft);
			}

			//----------- 2nd Neighbour (South) ------------

			// Only process this cell if this is a valid one
			if (isValid (row+1, col) == true)
			{
				if (isMine (row+1, col, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft);
			}

			//----------- 3rd Neighbour (East) ------------

			// Only process this cell if this is a valid one
			if (isValid (row, col+1) == true)
			{
				if (isMine (row, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft);
			}

			//----------- 4th Neighbour (West) ------------

			// Only process this cell if this is a valid one
			if (isValid (row, col-1) == true)
			{
				if (isMine (row, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft);
			}

			//----------- 5th Neighbour (North-East) ------------

			// Only process this cell if this is a valid one
			if (isValid (row-1, col+1) == true)
			{
				if (isMine (row-1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft);
			}

			//----------- 6th Neighbour (North-West) ------------

			// Only process this cell if this is a valid one
			if (isValid (row-1, col-1) == true)
			{
				if (isMine (row-1, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft);
			}

			//----------- 7th Neighbour (South-East) ------------

			// Only process this cell if this is a valid one
			if (isValid (row+1, col+1) == true)
			{
				if (isMine (row+1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft);
			}

			//----------- 8th Neighbour (South-West) ------------

			// Only process this cell if this is a valid one
			if (isValid (row+1, col-1) == true)
			{
				if (isMine (row+1, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col-1, movesLeft);
			}
		}

		return (false);
	}
}

// A Function to place the mines randomly
// on the board
void placeMines(int mines[][2], char realBoard[][SIDE])
{
	bool mark[SIDE*SIDE];

	memset(mark, false, sizeof (mark));

	// Continue until all random mines have been created.
	for (int i=0; i<MINES; )
	{
		int random = rand() % (SIDE*SIDE);
		int x = random / SIDE;
		int y = random % SIDE;

		// Add the mine if no mine is placed at this
		// position on the board
		if (mark[random] == false)
		{
			// Row Index of the Mine
			mines[i][0] = x;
			// Column Index of the Mine
			mines[i][1] = y;

			// Place the mine
			realBoard[mines[i][0]][mines[i][1]] = '*';
			mark[random] = true;
			i++;
		}
	}

	return;
}

// A Function to initialise the game
void initialise (char realBoard[][SIDE], char myBoard[][SIDE])
{
	// Assign all the cells as mine-free
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
		{
			myBoard[i][j] = realBoard[i][j] = '-';
		}
	}

	return;
}

// A Function to cheat by revealing where the mines are
// placed.
void cheatMinesweeper (char realBoard[][MAXSIDE])
{
	printf ("The mines locations are-\n");
	printBoard (realBoard);
	return;
}

// A function to replace the mine from (row, col) and put
// it to a vacant space
void replaceMine (int row, int col, char board[][MAXSIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
			{
				// Find the first location in the board
				// which is not having a mine and put a mine
				// there.
				if (board[i][j] != '*')
				{
					board[i][j] = '*';
					board[row][col] = '-';
					return;
				}
			}
	}
	return;
}

// A Function to play Minesweeper game
void playMinesweeper ()
{
	// Initially the game is not over
	bool gameOver = false;

	// Actual Board and My Board
	char realBoard[SIDE][SIDE], myBoard[SIDE][SIDE];

	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[MINES][2]; // Stores (x, y) coordinates of all mines.
	int moves[MAXSIDE][2]; // Stores (x, y) coordinates of the moves

	// Initialise the Game
	initialise (realBoard, myBoard);

	// Place the Mines randomly
	placeMines (mines, realBoard);

	// Assign Moves
	// If you want to make your own input move,
	// then the below function should be commnented
	assignMoves (moves, movesLeft);

	/*
	//If you want to cheat and know
	//where mines are before playing the game
	//then uncomment this part

	cheatMinesweeper(realBoard);
	*/

	// You are in the game until you have not opened a mine
	// So keep playing

	int currentMoveIndex = 0;
	while (gameOver == false)
	{
		printf ("Current Status of Board : \n");
		printBoard (myBoard);

		makeMove (&x, &y, moves, currentMoveIndex);

		// This is to guarantee that the first move is
		// always safe
		// If it is the first move of the game
		if (currentMoveIndex == 0)
		{
			// If the first move itself is a mine
			// then we remove the mine from that location
			if (isMine (x, y, realBoard) == true)
				replaceMine (x, y, realBoard);
		}

		currentMoveIndex ++;

		gameOver = playMinesweeperUtil (myBoard, realBoard, mines, x, y, &movesLeft);

		if ((gameOver == false) && (movesLeft == 0))
		{
			printf ("\nYou won !\n");
			gameOver = true;
		}
	}

	return;
}

// A Function to choose the difficulty level
// of the game
void chooseDifficultyLevel (int level)
{
	/*
	--> BEGINNER = 9 * 9 Cells and 10 Mines
	--> INTERMEDIATE = 16 * 16 Cells and 40 Mines
	--> ADVANCED = 24 * 24 Cells and 99 Mines
	*/

	if (level == BEGINNER)
	{
		SIDE = 9;
		MINES = 10;
	}

	if (level == INTERMEDIATE)
	{
		SIDE = 16;
		MINES = 40;
	}

	if (level == ADVANCED)
	{
		SIDE = 24;
		MINES = 99;
	}

	return;
}

int    initialize_difficulty(void)
{
    char input[50];
    
    printf("Enter a difficulty level :\n");
    printf("'B' for Beginner     -> 9x9 grid     10 mines\n");
    printf("'I' for Intermediate -> 16x16 grid   40 mines\n");
    printf("'A' for Advanced     -> 24x24 grid   99 mines\n");
    printf("'C' for Custom\n");
    scanf("%s", input);

    if (!strcmp(input, "B") || !strcmp(input, "I") || !strcmp(input, "A") || !strcmp(input, "C")) {
        if (!strcmp(input, "C")) {
            printf("Enter side lengths (maximum 50) : ");
            scanf("%d", &SIDE);
            if (SIDE < 1 || SIDE > 50)
                return (printf("Incorrect side lengths, must be between 1 and 50\n"));
            printf("Enter number of mines (maximum 500 or 30%% of number of cells) : ");
            scanf("%d", &MINES);
            if (MINES < 1 || MINES > 500 || MINES > (SIDE*SIDE*0.3))
                return (printf("Incorrect number of mines, must be between 0 and %d\n", (int)(SIDE*SIDE*0.3)));
        }
        else {
            switch (*input) {
                case 'B':
                    chooseDifficultyLevel (BEGINNER);
                    break;
                case 'I':
                    chooseDifficultyLevel (INTERMEDIATE);
                    break;
                case 'A':
                    chooseDifficultyLevel (ADVANCED);
                    break;
            }
        }
    }
    else { 
        printf("Incorrect input!\n");
        return (1);
    }
    return (0);
}

// Driver Program to test above functions
int main()
{
    FLAGS = 0;

    // Initiate the random number generator so that
	// the same configuration doesn't arises
	srand(time(NULL));
    
    if (initialize_difficulty())
        return (1);

    char realBoard[SIDE][SIDE], myBoard[SIDE][SIDE];

	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[MINES][2]; // Stores (x, y) coordinates of all mines.
	int moves[MAXSIDE][2]; // Stores (x, y) coordinates of the moves

	// Initialise the Game
	initialise (realBoard, myBoard);
    // printf("Allo 1\n");

    // printf("%d %d\n", MINES, SIDE);
	// Place the Mines randomly
	placeMines (mines, realBoard);

	// playMinesweeper ();
	return (0);
}
