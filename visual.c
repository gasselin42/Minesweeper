/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:36:33 by gasselin          #+#    #+#             */
/*   Updated: 2022/01/21 11:45:25 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

int	get_pixel(t_sprite *sp, int x, int y)
{
	char	*pixel;

	pixel = sp->addr + (y * sp->len + x * (sp->bpp / 8));
	return (*(int *)pixel);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void fill_screen(t_ms *ms)
{
	for (int i = 10; i < ms->win_width - 10; i++) {
		for (int j = 10; j < ms->win_height - 10; j++) {
			if (j <= 60)
				my_mlx_pixel_put(ms->img[0], i, j, 0xFFFFFF);
			else
				my_mlx_pixel_put(ms->img[0], i, j, 0x000000);
		}
	}
}

t_sprite	*new_sprite(void *mlx, char *file)
{
	t_sprite	*sp;

	sp = calloc(1, sizeof(t_sprite));
	sp->img = mlx_xpm_file_to_image(mlx, file, &sp->width, &sp->height);
	sp->addr = mlx_get_data_addr(sp->img, &sp->bpp, &sp->len, &sp->endian);
	sp->file = file;
	return (sp);
}

t_img	*new_image(t_ms *ms)
{
	t_img	*img;

	img = calloc(1, sizeof(t_img));
	img->img = mlx_new_image(ms->mlx, ms->win_width, ms->win_height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->endian);
	return (img);
}

void	initialize_sprites(t_ms *ms)
{
	ms->sprites[0] = new_sprite(ms->mlx, "./assets/0.xpm");
	ms->sprites[1] = new_sprite(ms->mlx, "./assets/1.xpm");
	ms->sprites[2] = new_sprite(ms->mlx, "./assets/2.xpm");
	ms->sprites[3] = new_sprite(ms->mlx, "./assets/3.xpm");
	ms->sprites[4] = new_sprite(ms->mlx, "./assets/4.xpm");
	ms->sprites[5] = new_sprite(ms->mlx, "./assets/5.xpm");
	ms->sprites[6] = new_sprite(ms->mlx, "./assets/6.xpm");
	ms->sprites[7] = new_sprite(ms->mlx, "./assets/7.xpm");
	ms->sprites[8] = new_sprite(ms->mlx, "./assets/8.xpm");
	ms->sprites[PINK_SQR] = new_sprite(ms->mlx, "./assets/pink_square.xpm");
	ms->sprites[FLAG] = new_sprite(ms->mlx, "./assets/grey_square_flag.xpm");
	ms->sprites[BOMB_RED] = new_sprite(ms->mlx, "./assets/red_square_bomb.xpm");
	ms->sprites[BOMB_PINK] = new_sprite(ms->mlx, "./assets/pink_square_bomb.xpm");
	ms->sprites[BOMB_GREY] = new_sprite(ms->mlx, "./assets/grey_square_bomb.xpm");
	ms->sprites[HPIPE] = new_sprite(ms->mlx, "./assets/horizontal_pipe.xpm");
	ms->sprites[VPIPE] = new_sprite(ms->mlx, "./assets/vertical_pipe.xpm");
}

void	draw_tile(t_ms *ms, int index, int x, int y)
{
	int	i;
	int	j;
	int	color;

	j = 0;
	while (j < ms->sprites[index]->height)
	{
		i = 0;
		while (i < ms->sprites[index]->width)
		{
			color = get_pixel(ms->sprites[index], i, j);
			my_mlx_pixel_put(ms->img[0], x + i, y + j, color);
			++i;
		}
		++j;
	}
}

void	draw_game(t_ms *ms)
{
	for (int y = 0; y < SIDE; y++) {
		for (int x = 0; x < SIDE; x++) {
			switch (ms->realBoard[y][x]) {
				case '-':
					draw_tile(ms, PINK_SQR, 10 + (x * 29), 60 + 10 + (y * 29));
					break;
				case 'F':
					draw_tile(ms, FLAG, 10 + (x * 29), 60 + 10 + (y * 29));
					break;
				case '0':
					draw_tile(ms, 0, 10 + (x * 29), 60 + 10 + (y * 29));
					break;
				case '1':
					draw_tile(ms, 1, 10 + (x * 29), 60 + 10 + (y * 29));
					break;
				case '2':
					draw_tile(ms, 2, 10 + (x * 29), 60 + 10 + (y * 29));
					break;
				case '3':
					draw_tile(ms, 3, 10 + (x * 29), 60 + 10 + (y * 29));
					break;
				case '4':
					draw_tile(ms, 4, 10 + (x * 29), 60 + 10 + (y * 29));
					break;
				case '5':
					draw_tile(ms, 5, 10 + (x * 29), 60 + 10 + (y * 29));
					break;
				case '6':
					draw_tile(ms, 6, 10 + (x * 29), 60 + 10 + (y * 29));
					break;
				case '7':
					draw_tile(ms, 7, 10 + (x * 29), 60 + 10 + (y * 29));
					break;
				case '8':
					draw_tile(ms, 8, 10 + (x * 29), 60 + 10 + (y * 29));
					break;
				case '*':
					draw_tile(ms, BOMB_RED, 10 + (x * 29), 60 + 10 + (y * 29));
					break;
			}
			if (y > 0 && x < SIDE)
				draw_tile(ms, HPIPE, 10 + (x * 29), 60 + 6 + (y * 29));
			if (x > 0 && y < SIDE)
				draw_tile(ms, VPIPE, 6 + (x * 29), 60 + 10 + (y * 29));
		}
	}
}

void	swap_maps(t_ms *ms)
{
	t_img *tmp;

	tmp = ms->img[0];
	ms->img[0] = ms->img[1];
	ms->img[1] = tmp;
}

int	close_win(t_ms *ms)
{
	free (ms->img[0]);
	free (ms->img[1]);
	for (int i = 0; i < N_SPRITE; i++)
		free (ms->sprites[i]);
	mlx_destroy_window(ms->mlx, ms->win);
	exit (0);
	return (0);
}

int	deal_key(int key, t_ms * ms)
{
	if (key == 0x35)
		close_win(ms);
	return (0);
}

bool get_square_index(int *sqr_x, int *sqr_y, int x, int y)
{
	y -= 70;
	x -= 10;

	int tmp_x = x % 29;
	int tmp_y = y % 29;

	if (tmp_x >= 25 || tmp_y >= 25)
		return false;
	
	(*sqr_x) = (int)(x / 29);
	(*sqr_y) = (int)(y / 29);

	return (true);
}

bool	is_opened(char c)
{
	if (c >= 48 && c <= 57)
		return (true);
	return (false);
}

int deal_mouse(int button, int x, int y, t_ms *ms)
{
	int sqr_x = 0, sqr_y = 0;

	if (y >= 70 && y <= ms->win_height - 10 &&
		x >= 10 && x <= ms->win_width - 10)
	{
		if (get_square_index(&sqr_x, &sqr_y, x, y))
		{
			if (is_opened(ms->myBoard[sqr_y][sqr_x]))
				return (0);
			if (button == 1)
			{
				if (ms->myBoard[sqr_y][sqr_x] == 'F')
					return (0);
				// playMinesweeperUtil(ms, sqr_y, sqr_x);
			}
			
			if (button == 2)
			{
				
			}
		}
	}
	return (0);
}

// int	mouse_move(int x, int y, t_ms *ms) {}

void	execute(t_ms *ms)
{
	ms->mlx = mlx_init();
	ms->win = mlx_new_window(ms->mlx, ms->win_width, ms->win_height, "Minesweeper");
	initialize_sprites(ms);
	ms->img[0] = new_image(ms);
	ms->img[1] = new_image(ms);
	ms->movesLeft = SIDE * SIDE - MINES;
	fill_screen(ms);
	draw_game(ms);
	// swap_maps(ms);
	mlx_put_image_to_window(ms->mlx, ms->win, ms->img[0]->img, 0, 0);
	// mlx_mouse_hook(ms->win, deal_mouse, ms);
	// mlx_hook(ms->win, 6, 0, mouse_move, ms);  // Button hoovering
	mlx_hook(ms->win, 02, 1L << 0, deal_key, ms);
	mlx_hook(ms->win, 17, 1L << 17, close_win, ms);
	mlx_loop(ms->mlx);
}