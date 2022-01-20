/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minesweeper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:36:55 by gasselin          #+#    #+#             */
/*   Updated: 2022/01/20 10:50:59 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "./mlx/mlx.h"

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
#define N_SPRITE 7

#define PINK_SQR 0
#define GREY_SQR 1
#define RED_SQR 2
#define HPIPE 3
#define VPIPE 4
#define COG 5
#define FLAG 6

int SIDE; // side length of the board
int MINES; // number of mines on the board
int FLAGS; // number of flags on the map

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}	t_img;

typedef struct s_sprite
{
	void	*img;
	char	*file;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		len;
	int		endian;
}	t_sprite;

typedef struct s_ms {
	void	*mlx;
	void	*win;
	int		win_width;
	int		win_height;

	// new_image
	t_img	*img[2];

	//sprites
	t_sprite	*sprites[N_SPRITE];
}	t_ms;

bool 	isValid(int row, int col);
bool 	isMine (int row, int col, char board[][SIDE]);
void 	printBoard(char myBoard[][SIDE]);
int 	countAdjacentMines(int row ,int col ,int mines[][2], char realBoard[][SIDE]);
bool 	playMinesweeperUtil(char myBoard[][SIDE], char realBoard[][SIDE],
							int mines[][2], int row, int col, int *movesLeft);
void 	placeMines(int mines[][2], char realBoard[][SIDE]);
void 	playMinesweeper(t_ms *ms);
void 	chooseDifficultyLevel(int level);
int		initialize_difficulty(void);

void	execute(t_ms *ms);

#endif