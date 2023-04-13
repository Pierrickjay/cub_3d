/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:01:31 by pjay              #+#    #+#             */
/*   Updated: 2023/04/13 15:10:40 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	my_mlx_pixel_put(t_cbdata *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mini[data->mini_img].addr \
		+ (y * data->mini[data->mini_img].line_length + x \
		* (data->mini[data->mini_img].bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	mini_tile_file(t_cbdata *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	tile;

	tile = data->mini[data->mini_img].mini_tile_size;
	i = -1;
	while (++i < tile)
	{
		j = -1;
		while (++j < tile)
			my_mlx_pixel_put(data, x * tile + i, y * tile + j, color);
	}
}

void	mini_pos_file(t_cbdata *data)
{
	int	i;
	int	j;
	int	tile;
	int	posx;
	int	posy;

	tile = data->mini[data->mini_img].mini_tile_size;
	if (tile < 1)
		tile = 1;
	posx = (int)data->pos_x * tile;
	posy = (int)data->pos_y * tile;
	posx /= BLOCK_SIZE;
	posy /= BLOCK_SIZE;
	i = -1;
	while (++i < tile / 3)
	{
		j = -1;
		while (++j < tile / 3)
			my_mlx_pixel_put(data, posx - tile / 6 + j //faire diviser par 4 pour lavoir dans le coin a droite
				, posy - tile / 6  + i, 0x00FF0000);
	}
}

void	redraw_mini_map(t_cbdata *data)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	//render_3d(data);
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				color = 0x4848BB;
			else if (cell_isa(data->map[y][x], CELL_SOFT))
				color = 0xF4D691;
			else
				color = 0x000000;
			mini_tile_file(data, x, y, color);
			x++;
		}
		y++;
	}
	draw_lines(data);
	mini_pos_file(data);
	render_3d(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
		data->mini[data->mini_img].img, 0, 0);
}
