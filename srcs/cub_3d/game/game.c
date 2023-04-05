/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:12:02 by pjay              #+#    #+#             */
/*   Updated: 2023/04/05 15:40:43 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	my_mlx_pixel_put(t_cbdata *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mini.addr + (y * data->mini.line_length + x * (data->mini.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	mini_tile_file(t_cbdata *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	tile;

	tile = data->mini.mini_tile_size;
	i = -1;
	while (++i < tile)
	{
		j = -1;
		while (++j < tile)
			my_mlx_pixel_put(data, x * tile + i, y * tile + j, color);
	}
}

void	init_mini_map(t_cbdata *data)
{
	int	x;
	int	y;
	int	color;

	data->mini.img = mlx_new_image(data->mlx, MINI_X, MINI_Y);
	data->mini.addr = mlx_get_data_addr(data->mini.img,
			&data->mini.bits_per_pixel,
			&data->mini.line_length, &data->mini.endian);
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				color = 0x4848BB;
			else if (cell_isa(data->map[y][x], CELL_SOFT) )
				color = 0xF4D691;
			else
				color = 0x000000;
			mini_tile_file(data, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->mini.img, 0, 0);
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
	mlx_loop(data->mlx);
}
