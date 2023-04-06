/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:12:02 by pjay              #+#    #+#             */
/*   Updated: 2023/04/06 10:58:37 by pjay             ###   ########.fr       */
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
	int	color;
	int	posx;
	int	posy;


	color = 0x00FF0000;
	tile = data->mini[data->mini_img].mini_tile_size;
	if (tile == 0)
		tile = 1;
	posx = data->pos_x * tile;
	posy = data->pos_y * tile;
	posx /= 64;
	posy /= 64;
	i = -1;
	while (++i < tile / 3)
	{
		j = -1;
		while (++j < tile / 3)
			my_mlx_pixel_put(data, posx - tile / 6 + j, posy - tile / 6 + i, color);
	}
}

void	init_mini_map(t_cbdata *data)
{
	data->mini[0].img = mlx_new_image(data->mlx, MINI_X, MINI_Y);
	data->mini[0].addr = mlx_get_data_addr(data->mini[0].img,
			&data->mini[0].bits_per_pixel,
			&data->mini[0].line_length, &data->mini[0].endian);
	data->mini[1].img = mlx_new_image(data->mlx, MINI_X, MINI_Y);
	data->mini[1].addr = mlx_get_data_addr(data->mini[1].img,
			&data->mini[1].bits_per_pixel,
			&data->mini[1].line_length, &data->mini[1].endian);
}

void	redraw_mini_map(t_cbdata *data)
{
	int	x;
	int	y;
	int	color;

	y = 0;
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
	mini_pos_file(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->mini[data->mini_img].img, 0, 0);
	data->mini_img++;
	if (data->mini_img == 2)
		data->mini_img = 0;
}

int	run_loop(void *voiddata)
{
	t_cbdata	*data;

	data = (t_cbdata *)voiddata;
	if (data->redraw == 1)
	{
		DP
		redraw_mini_map(data);
		data->redraw = 0;
	}
	return (0);
}

void	init_game(t_cbdata *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		cb_exit(data, "MLX failed");
	//set_image(data);
	data->mlx_win = mlx_new_window(data->mlx, MINI_X, MINI_Y,
			"mini_map");
	if (!data->mlx_win)
		cb_exit(data, "MLX failed");
	set_hooks(data);
	init_mini_map(data);
	mlx_loop_hook(data->mlx, run_loop, data);
	mlx_loop(data->mlx);
}
