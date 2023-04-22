/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:01:31 by pjay              #+#    #+#             */
/*   Updated: 2023/04/22 13:51:23 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	my_mlx_pixel_put(t_cbdata *data, int x, int y, int color)
{
	char	*dst;

	dst = data->image[data->img].addr \
		+ (y * data->image[data->img].line_length + x \
		* (data->image[data->img].bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	mini_tile_file(t_cbdata *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	tile;

	tile = data->image[data->img].mini_tile_size;
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

	tile = data->image[data->img].mini_tile_size;
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
			my_mlx_pixel_put(data, posx - tile / 6 + j, \
					posy - tile / 6 + i, 0x00FF0000);
	}
}

void	redraw_mini_map(t_cbdata *data)
{
	draw_lines(data);
	render_3d(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	data->image[data->img].img, 0, 0);
}
