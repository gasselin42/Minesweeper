/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minesweeper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:36:55 by gasselin          #+#    #+#             */
/*   Updated: 2022/01/23 12:26:56 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "../mlx_mac/mlx.h"

#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>

#ifdef _LINUX
#define RCLICK 3
#define ESC_BUTTON 65307
#else
#define RCLICK 2
#define ESC_BUTTON 53
#endif

#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCED 2
#define N_SPRITE 29

#define MAXSIDE 40
#define MAXMINES 400

#define PINK_SQR 19
#define GREY_SQR 20
#define FLAG 21
#define BOMB_RED 22
#define BOMB_PINK 23
#define BOMB_GREY 24
#define HPIPE 25
#define VPIPE 26
#define MINUS 27
#define DARK_PINK 28

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
	int		minesLeft;
	long int start_time;
	long int stop_time;
	int		crt_x;
	int		crt_y;

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
	bool	start_timer;
	bool	gameWon;
}	t_ms;

bool 	isValid(int row, int col);
bool 	isMine (int row, int col, char board[][MAXSIDE]);
void 	printBoard(char myBoard[][MAXSIDE]);
int 	countAdjacentMines(int row ,int col , char realBoard[][MAXSIDE]);
bool 	playMinesweeperUtil(t_ms *ms, int row, int col);
void 	placeMines(t_ms *ms);
void 	playMinesweeper(t_ms *ms);
void 	chooseDifficultyLevel(int level);
int		initialize_difficulty(void);

void		execute(t_ms *ms);
long int	get_time(void);

#endif