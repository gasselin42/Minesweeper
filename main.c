/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:35:05 by gasselin          #+#    #+#             */
/*   Updated: 2022/01/19 16:43:32 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

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
bool isMine (int row, int col, char board[][SIDE])
{
	if (board[row][col] == '*')
		return (true);
	else
		return (false);
}

// A Function to print the current gameplay board
void printBoard(char myBoard[][SIDE])
{
	int i,j;

	printf ("  ");
	if (SIDE >= 10)
		printf (" ");

	for (i=0; i<SIDE; i++)
		printf ("%d ", i);

	printf ("\n");

	for (i=0; i<SIDE; i++)
	{
		if (SIDE >= 10 && i < 10)
			printf (" ");
		printf ("%d ", i);

		for (j=0; j<SIDE; j++)
			printf ("%c ", myBoard[i][j]);
		printf ("\n");
	}
	return;
}

// A Function to count the number of
// mines in the adjacent cells
int countAdjacentMines(int row ,int col ,int mines[][2], char realBoard[][SIDE])
{

	int i;
	int count = 0;

	if (isValid (row-1, col) == true)
	{
		if (isMine (row-1, col, realBoard) == true)
			count++;
	}

	if (isValid (row+1, col) == true)
	{
		if (isMine (row+1, col, realBoard) == true)
			count++;
	}

	if (isValid (row, col+1) == true)
	{
		if (isMine (row, col+1, realBoard) == true)
			count++;
	}

	if (isValid (row, col-1) == true)
	{
		if (isMine (row, col-1, realBoard) == true)
			count++;
	}

	if (isValid (row-1, col+1) == true)
	{
		if (isMine (row-1, col+1, realBoard) == true)
			count++;
	}

	if (isValid (row-1, col-1) == true)
	{
		if (isMine (row-1, col-1, realBoard) == true)
			count++;
	}

	if (isValid (row+1, col+1) == true)
	{
		if (isMine (row+1, col+1, realBoard) == true)
			count++;
	}

	if (isValid (row+1, col-1) == true)
	{
		if (isMine (row+1, col-1, realBoard) == true)
			count++;
	}

	return (count);
}

// A Recursive Function to play the Minesweeper Game
bool playMinesweeperUtil(char myBoard[][SIDE], char realBoard[][SIDE],
			int mines[][2], int row, int col, int *movesLeft)
{

	// Base Case of Recursion
	if (myBoard[row][col] != '-')
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
		int count = countAdjacentMines(row, col, mines, realBoard);
		(*movesLeft)--;

		myBoard[row][col] = count + '0';

		if (!count)
		{
			if (isValid (row-1, col) == true)
			{
				if (isMine (row-1, col, realBoard) == false)
				playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft);
			}

			if (isValid (row+1, col) == true)
			{
				if (isMine (row+1, col, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft);
			}

			if (isValid (row, col+1) == true)
			{
				if (isMine (row, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft);
			}

			if (isValid (row, col-1) == true)
			{
				if (isMine (row, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft);
			}

			if (isValid (row-1, col+1) == true)
			{
				if (isMine (row-1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft);
			}

			if (isValid (row-1, col-1) == true)
			{
				if (isMine (row-1, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft);
			}

			if (isValid (row+1, col+1) == true)
			{
				if (isMine (row+1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft);
			}

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

// A Function to play Minesweeper game
void playMinesweeper (t_ms *ms)
{
	// Initially the game is not over
	bool gameOver = false;

	// Actual Board and My Board
	char realBoard[SIDE][SIDE], myBoard[SIDE][SIDE];

	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[MINES][2]; // Stores (x, y) coordinates of all mines.
	int moves[SIDE][2]; // Stores (x, y) coordinates of the moves

	// Initialise the Game
	initialise (realBoard, myBoard);

	// Place the Mines randomly
	placeMines (mines, realBoard);

	// You are in the game until you have not opened a mine
	// So keep playing

	int currentMoveIndex = 0;
	while (gameOver == false)
	{
		printf ("Current Status of Board : \n");
		printBoard (myBoard);

		printf("Enter coordinates of your next move (x y) : ");
		scanf("%d %d", &x, &y);

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
	t_ms	ms;
    FLAGS = 0;

    // Initiate the random number generator so that
	// the same configuration doesn't arises
	srand(time(NULL));

    if (initialize_difficulty())
        return (1);

	ms.win_height = (10 * 3) + 50 + (20 * SIDE);
	ms.win_width = (10 * 2) + (20 * SIDE);
	execute(&ms);
	// playMinesweeper (&ms);
	return (0);
}
