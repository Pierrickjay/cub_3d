/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:12:02 by pjay              #+#    #+#             */
/*   Updated: 2023/04/06 11:16:10 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"


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

int	run_loop(void *voiddata)
{
	t_cbdata	*data;

	data = (t_cbdata *)voiddata;
	if (data->redraw == 1)
	{
		//DP
		redraw_mini_map(data);
		data->mini_img++;
		if (data->mini_img == 2)
		data->mini_img = 0;
		data->redraw = 0;
	}
	return (0);
}

void	init_game(t_cbdata *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		cb_exit(data, "MLX failed");
	data->mlx_win = mlx_new_window(data->mlx, MINI_X, MINI_Y,
			"mini_map");
	if (!data->mlx_win)
		cb_exit(data, "MLX failed");
	set_hooks(data);
	init_mini_map(data);
	mlx_loop_hook(data->mlx, run_loop, data);
	mlx_loop(data->mlx);
}
