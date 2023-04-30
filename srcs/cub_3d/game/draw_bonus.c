/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:27:41 by pjay              #+#    #+#             */
/*   Updated: 2023/04/30 11:30:32 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

static int	set_mini_color(t_cbdata *data, int x, int y);
static void	mini_pos_file(t_cbdata *data);

void	my_mlx_pixel_put(t_cbdata *data, int x, int y, int color)
{
	char	*dst;

	dst = data->image[data->img].addr \
		+ (y * data->image[data->img].line_len + x \
		* (data->image[data->img].bpp / 8));
	*(unsigned int *)dst = color;
}

void	mini_tile_file(t_cbdata *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	tile;

	tile = data->mini_tile_size;
	i = -1;
	while (++i < tile)
	{
		j = -1;
		while (++j < tile)
			my_mlx_pixel_put(data, x * tile + i, y * tile + j, color);
	}
}

void	redraw_mini_map(t_cbdata *data)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			color = set_mini_color(data, x, y);
			mini_tile_file(data, x, y, color);
		}
	}
	draw_lines(data);
	mini_pos_file(data);
	render_3d(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
		data->image[data->img].mlx_img, 0, 0);
}

static int	set_mini_color(t_cbdata *data, int x, int y)
{
	if (data->map[y][x] == '1')
		return (0x4848BB);
	else if (cell_isa(data->map[y][x], CELL_SOFT_BONUS))
		return (0xF4D691);
	else
		return (0x000000);
}

static void	mini_pos_file(t_cbdata *data)
{
	int	i;
	int	j;
	int	tile;
	int	posx;
	int	posy;

	tile = data->mini_tile_size;
	if (tile < 1)
		tile = 1;
	posx = ((int)data->pos_x * tile) / BLOCK_SIZE;
	posy = ((int)data->pos_y * tile) / BLOCK_SIZE;
	i = -1;
	while (++i < tile / 3)
	{
		j = -1;
		while (++j < tile / 3)
			my_mlx_pixel_put(data, posx - tile / 6 + j, \
					posy - tile / 6 + i, 0x00FF0000);
	}
}
