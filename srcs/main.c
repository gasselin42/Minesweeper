/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:35:05 by gasselin          #+#    #+#             */
/*   Updated: 2022/02/02 12:13:59 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minesweeper.h"

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not
bool isValid(t_ms *ms, int row, int col)
{
	// Returns true if row number and column number
	// is in range
	return (row >= 0) && (row < ms->SIDE) &&
			(col >= 0) && (col < ms->SIDE);
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

// A Function to count the number of
// mines in the adjacent cells
int countAdjacentMines(t_ms *ms, int row ,int col, char realBoard[][MAXSIDE])
{
	int count = 0;

	if (isValid (ms, row-1, col) == true)
	{
		if (isMine (row-1, col, realBoard) == true)
			count++;
	}

	if (isValid (ms, row+1, col) == true)
	{
		if (isMine (row+1, col, realBoard) == true)
			count++;
	}

	if (isValid (ms, row, col+1) == true)
	{
		if (isMine (row, col+1, realBoard) == true)
			count++;
	}

	if (isValid (ms, row, col-1) == true)
	{
		if (isMine (row, col-1, realBoard) == true)
			count++;
	}

	if (isValid (ms, row-1, col+1) == true)
	{
		if (isMine (row-1, col+1, realBoard) == true)
			count++;
	}

	if (isValid (ms, row-1, col-1) == true)
	{
		if (isMine (row-1, col-1, realBoard) == true)
			count++;
	}

	if (isValid (ms, row+1, col+1) == true)
	{
		if (isMine (row+1, col+1, realBoard) == true)
			count++;
	}

	if (isValid (ms, row+1, col-1) == true)
	{
		if (isMine (row+1, col-1, realBoard) == true)
			count++;
	}

	return (count);
}

void	place_indexes(t_ms *ms)
{
	for (int i=0; i<ms->SIDE; i++)
	{
		for (int j=0; j<ms->SIDE; j++)
		{
			if (ms->realBoard[i][j] != '*')
				ms->realBoard[i][j] = '0' + countAdjacentMines(ms, i, j, ms->realBoard);
		}
	}
}

// A Recursive Function to play the Minesweeper Game
bool playMinesweeperUtil(t_ms *ms, int row, int col)
{

	// Base Case of Recursion
	if (ms->myBoard[row][col] != '-')
		return (false);

	// You opened a mine
	// You are going to lose
	if (ms->realBoard[row][col] == '*')
	{
		ms->myBoard[row][col] = '*';

		// for (i = 0; i < MINES; i++)
		// 	ms->myBoard[ms->mines[i][0]][ms->mines[i][1]] = '*';
		ms->gameOver = true;
		ms->stop_time = get_time() - ms->start_time;
		return (true) ;
	}

	else
	{
		ms->myBoard[row][col] = ms->realBoard[row][col];

		if (ms->realBoard[row][col] == '0')
		{
			if (isValid (ms, row-1, col) == true)
			{
				if (isMine (row-1, col, ms->realBoard) == false)
					playMinesweeperUtil(ms, row-1, col);
			}

			if (isValid (ms, row+1, col) == true)
			{
				if (isMine (row+1, col, ms->realBoard) == false)
					playMinesweeperUtil(ms, row+1, col);
			}

			if (isValid (ms, row, col+1) == true)
			{
				if (isMine (row, col+1, ms->realBoard) == false)
					playMinesweeperUtil(ms, row, col+1);
			}

			if (isValid (ms, row, col-1) == true)
			{
				if (isMine (row, col-1, ms->realBoard) == false)
					playMinesweeperUtil(ms, row, col-1);
			}

			if (isValid (ms, row-1, col+1) == true)
			{
				if (isMine (row-1, col+1, ms->realBoard) == false)
					playMinesweeperUtil(ms, row-1, col+1);
			}

			if (isValid (ms, row-1, col-1) == true)
			{
				if (isMine (row-1, col-1, ms->realBoard) == false)
					playMinesweeperUtil(ms, row-1, col-1);
			}

			if (isValid (ms, row+1, col+1) == true)
			{
				if (isMine (row+1, col+1, ms->realBoard) == false)
					playMinesweeperUtil(ms, row+1, col+1);
			}

			if (isValid (ms, row+1, col-1) == true)
			{
				if (isMine (row+1, col-1, ms->realBoard) == false)
					playMinesweeperUtil(ms, row+1, col-1);
			}
		}

		return (false);
	}
}

// A Function to place the mines randomly
// on the board
void placeMines(t_ms *ms)
{
	bool mark[ms->SIDE*ms->SIDE];

	memset(mark, false, sizeof (mark));

	// Continue until all random mines have been created.
	for (int i = 0; i < ms->MINES; )
	{
		int random = rand() % (ms->SIDE*ms->SIDE);
		int x = random / ms->SIDE;
		int y = random % ms->SIDE;

		// Add the mine if no mine is placed at this
		// position on the board
		if (mark[random] == false)
		{
			// Row Index of the Mine
			ms->mines[i][0] = x;
			// Column Index of the Mine
			ms->mines[i][1] = y;

			// Place the mine
			ms->realBoard[ms->mines[i][0]][ms->mines[i][1]] = '*';
			mark[random] = true;
			i++;
		}
	}
}

// A Function to initialise the game
void initialise (t_ms *ms)
{
	// Assign all the cells as mine-free
	for (int i=0; i<ms->SIDE; i++)
	{
		for (int j=0; j<ms->SIDE; j++)
		{
			ms->myBoard[i][j] = '-';
			ms->realBoard[i][j] = '-';
		}
	}
}

// A Function to choose the difficulty level
// of the game
void chooseDifficultyLevel (t_ms *ms, int level)
{
	if (level == BEGINNER)
	{
		ms->SIDE = 9;
		ms->MINES = 10;
	}

	if (level == INTERMEDIATE)
	{
		ms->SIDE = 16;
		ms->MINES = 40;
	}

	if (level == ADVANCED)
	{
		ms->SIDE = 24;
		ms->MINES = 99;
	}
}

int    initialize_difficulty(t_ms *ms)
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
            printf("Enter side lengths (minimum 7, maximum 40) : ");
            scanf("%d", &ms->SIDE);
            if (ms->SIDE < 7 || ms->SIDE > 40)
                return (printf("Incorrect side lengths, must be between 7 and 40\n"));
            printf("Enter number of mines (maximum 400 or 30%% of number of cells) : ");
            scanf("%d", &ms->MINES);
            if (ms->MINES < 1 || ms->MINES > 400 || ms->MINES > (ms->SIDE*ms->SIDE*0.3))
                return (printf("Incorrect number of mines, must be between 0 and %d\n", (int)(ms->SIDE*ms->SIDE*0.3)));
        }
        else {
            switch (*input) {
                case 'B':
                    chooseDifficultyLevel (ms, BEGINNER);
                    break;
                case 'I':
                    chooseDifficultyLevel (ms, INTERMEDIATE);
                    break;
                case 'A':
                    chooseDifficultyLevel (ms, ADVANCED);
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

void	init_grids(t_ms *ms)
{
	for (int i = 0; i < MAXSIDE; i++) {
		memset(ms->realBoard[i], '\0', MAXSIDE);
		memset(ms->myBoard[i], '\0', MAXSIDE);
	}
}

int main()
{
	t_ms	ms;
    ms.FLAGS = 0;

    // Initiate the random number generator so that
	// the same configuration doesn't arises
	srand(time(NULL));

	ms.gameOver = false;
	ms.start_timer = false;
	ms.gameWon = false;

	ms.crt_x = 0;
	ms.crt_y = 0;

    if (initialize_difficulty(&ms))
	{
        return (1);
	}

	init_grids(&ms);
	
	ms.win_height = (10 * 3) + 50 + (25 * ms.SIDE) + (4 * (ms.SIDE - 1));
	ms.win_width = (10 * 2) + (25 * ms.SIDE) + (4 * (ms.SIDE - 1));

	// Initialise the Game
	initialise (&ms);

	// Place the Mines randomly
	placeMines (&ms);

	// Place the indexes on realBoard
	place_indexes(&ms);
	
	execute(&ms);
	
	return (0);
}
