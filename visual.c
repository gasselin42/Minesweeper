/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:36:33 by gasselin          #+#    #+#             */
/*   Updated: 2022/01/19 16:46:17 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

void	my_mlx_pixel_put(t_ms *ms, int x, int y, int color)
{
	char	*dst;

	dst = ms->addr + (y * ms->len + x * (ms->bpp / 8));
	*(unsigned int*)dst = color;
}

void fill_screen(t_ms *ms) {
	for (int i = 10; i < ms->win_width - 10; i++) {
		for (int j = 10; j < ms->win_height - 10; j++) {	
			my_mlx_pixel_put(ms, i, j, 0xD4D0D0);
		}
	}
}

void	execute(t_ms *ms) {
	ms->mlx = mlx_init();
	ms->win = mlx_new_window(ms->mlx, ms->win_width, ms->win_height, "Minesweeper");
	ms->img = mlx_new_image(ms->mlx, ms->win_width, ms->win_height);
	ms->addr = mlx_get_data_addr(ms->img, &ms->bpp, &ms->len, &ms->endian);
	fill_screen(ms);
	mlx_put_image_to_window(ms->mlx, ms->win, ms->img, 0, 0);
	mlx_loop(ms->mlx);
}