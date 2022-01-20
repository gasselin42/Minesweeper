/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:36:33 by gasselin          #+#    #+#             */
/*   Updated: 2022/01/20 12:03:48 by gasselin         ###   ########.fr       */
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
			if (j < 60)
				my_mlx_pixel_put(ms->img[1], i, j, 0xFFFFFF);
			else
				my_mlx_pixel_put(ms->img[1], i, j, 0x000000);
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
	ms->sprites[PINK_SQR] = new_sprite(ms->mlx, "./assets/pink_square.xpm");
	ms->sprites[GREY_SQR] = new_sprite(ms->mlx, "./assets/grey_square.xpm");
	ms->sprites[RED_SQR] = new_sprite(ms->mlx, "./assets/red_square.xpm");
	ms->sprites[HPIPE] = new_sprite(ms->mlx, "./assets/horizontal_pipe.xpm");
	ms->sprites[VPIPE] = new_sprite(ms->mlx, "./assets/vertical_pipe.xpm");
	ms->sprites[COG] = new_sprite(ms->mlx, "./assets/cog.xpm");
	ms->sprites[FLAG] = new_sprite(ms->mlx, "./assets/flag.xpm");
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
			my_mlx_pixel_put(ms->img[1], x + i, y + j, color);
			++i;
		}
		++j;
	}
}

void	draw_game(t_ms *ms)
{
	for (int y = 0; y < SIDE; y++) {
		for (int x = 0; x < SIDE; x++) {
			draw_tile(ms, PINK_SQR, 10 + (x * 28), 60 + 10 + (y * 28));
			if (y > 0 && x < SIDE)
				draw_tile(ms, HPIPE, 10 + (x * 28), 60 + 7 + (y * 28));
			if (x > 0 && y < SIDE)
				draw_tile(ms, VPIPE, 7 + (x * 28), 60 + 10 + (y * 28));
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

void	execute(t_ms *ms)
{
	ms->mlx = mlx_init();
	ms->win = mlx_new_window(ms->mlx, ms->win_width, ms->win_height, "Minesweeper");
	initialize_sprites(ms);
	ms->img[0] = new_image(ms);
	ms->img[1] = new_image(ms);
	fill_screen(ms);
	draw_game(ms);
	swap_maps(ms);
	mlx_put_image_to_window(ms->mlx, ms->win, ms->img[0]->img, 0, 0);
	mlx_hook(ms->win, 02, 1L << 0, deal_key, ms);
	mlx_hook(ms->win, 17, 1L << 17, close_win, ms);
	mlx_loop(ms->mlx);
}