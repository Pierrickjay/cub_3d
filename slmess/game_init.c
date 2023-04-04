/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:13:44 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/04 12:36:07 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	init_game(t_cbdata *data)
{
	data->mlx = mlx_init();
	if (NULL == data->mlx)
		game_exit(data, MLX);
	data->win = mlx_new_window(data->mlx, \
			TILE_SIZE * data->map.size_x, \
			TILE_SIZE * (data->map.size_y), "Cub 3D");
	if (NULL == data->win)
		game_exit(data, MLX);
	start_game(data);
}

void	start_game(t_cbdata *data)
{
	mlx_hook(data->win, 2, (1L << 0), key_pressed, data);
	mlx_hook(data->win, 3, (1L << 1), key_released, data);
	mlx_loop_hook(data->mlx, next_frame, data);
	mlx_hook(data->win, 17, 0L, the_end, data);
	load_pic_files(data);
	draw_map(data);
	mlx_loop(data->mlx);
}

void	game_exit(t_cbdata *data, char *msg)
{
	int	i;

	i = -1;
	while (++i < IMG_MAX)
		mlx_destroy_image(data->mlx, data->images[i]);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	if (msg != NULL)
		error_exit(data, msg);
	else
		clean_exit(data, 0);
}

void	cb_img_to_win(t_cbdata *data, void *img, size_t x, size_t y)
{
	mlx_put_image_to_window(data->mlx, data->win, img, \
			TILE_SIZE * x, TILE_SIZE * y);
}
