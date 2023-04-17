/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:12:02 by pjay              #+#    #+#             */
/*   Updated: 2023/04/17 15:09:48 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	init_render(t_cbdata *data)
{
	data->image[0].img = mlx_new_image(data->mlx, PLANE_X, PLANE_Y);
	data->image[0].addr = mlx_get_data_addr(data->image[0].img,
			&data->image[0].bits_per_pixel,
			&data->image[0].line_length, &data->image[0].endian);
	data->image[1].img = mlx_new_image(data->mlx, PLANE_X, PLANE_Y);
	data->image[1].addr = mlx_get_data_addr(data->image[1].img,
			&data->image[1].bits_per_pixel,
			&data->image[1].line_length, &data->image[1].endian);
}

int	run_loop(void *voiddata)
{
	t_cbdata	*data;

	data = (t_cbdata *)voiddata;
	// if (data->redraw == 1)
	// { si on laisse ca cela fonctionne mais le jeu freeze
		change_pos_player(data);
		change_view_player(data);
		redraw_mini_map(data);
		data->img++;
		if (data->img == 2)
			data->img = 0;
	// 	data->redraw = 0;
	// }
	return (0);
}

void	init_game(t_cbdata *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		cb_exit(data, "MLX failed");
	data->mlx_win = mlx_new_window(data->mlx, PLANE_X, PLANE_Y,
			"mini_map");
	if (!data->mlx_win)
		cb_exit(data, "MLX failed");
	set_hooks(data);
	init_render(data);
	load_img(data);
	mlx_loop_hook(data->mlx, run_loop, data);
	mlx_loop(data->mlx);
}
