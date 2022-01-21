/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minesweeper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:36:55 by gasselin          #+#    #+#             */
/*   Updated: 2022/01/21 11:42:45 by gasselin         ###   ########.fr       */
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
#define N_SPRITE 16

#define MAXSIDE 40
#define MAXMINES 400

#define PINK_SQR 9
#define FLAG 10
#define BOMB_RED 11
#define BOMB_PINK 12
#define BOMB_GREY 13
#define HPIPE 14
#define VPIPE 15

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
	int		movesLeft;

	// new_images
	t_img	*img[2];

	// sprites
	t_sprite	*sprites[N_SPRITE];

	// grids
	char	realBoard[MAXSIDE][MAXSIDE];
	char	myBoard[MAXSIDE][MAXSIDE];
	int		mines[MAXMINES][2];

	// bool switches
	bool	gameOver;
}	t_ms;

bool 	isValid(int row, int col);
bool 	isMine (int row, int col, char board[][MAXSIDE]);
void 	printBoard(char myBoard[][MAXSIDE]);
int 	countAdjacentMines(int row ,int col ,int mines[MAXMINES][2], char realBoard[][MAXSIDE]);
bool 	playMinesweeperUtil(t_ms *ms, int row, int col);
void 	placeMines(t_ms *ms);
void 	playMinesweeper(t_ms *ms);
void 	chooseDifficultyLevel(int level);
int		initialize_difficulty(void);

void	execute(t_ms *ms);

#endif