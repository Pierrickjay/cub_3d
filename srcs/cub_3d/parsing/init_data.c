/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:33:14 by pjay              #+#    #+#             */
/*   Updated: 2023/04/12 16:20:38 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	load_img(t_cbdata *data/*, t_img *wall*/)
{
	if (!data->mlx)
	{
		DP
		cb_exit(data, "MLX FAILED");
		exit(0);
	}
	data->texture.wall_n.mlx_img = mlx_xpm_file_to_image(data->mlx, data->n_file,
		&data->texture.wall_n.width, &data->texture.wall_n.heigth);
	data->texture.wall_e.mlx_img = mlx_xpm_file_to_image(data->mlx, data->e_file,
		&data->texture.wall_e.width, &data->texture.wall_e.heigth);
	data->texture.wall_s.mlx_img = mlx_xpm_file_to_image(data->mlx,  data->s_file,
		&data->texture.wall_s.width, &data->texture.wall_s.heigth);
	data->texture.wall_w.mlx_img = mlx_xpm_file_to_image(data->mlx, data->w_file,
		&data->texture.wall_w.width, &data->texture.wall_w.heigth);
	if (!data->texture.wall_n.mlx_img || !data->texture.wall_s.mlx_img || !data->texture.wall_e.mlx_img || !data->texture.wall_w.mlx_img)
	{
		printf("n =|%s|\n", data->n_file);
		printf("e =|%s|\n", data->e_file);
		printf("w =|%s|\n", data->w_file);
		printf("s= |%s|\n", data->s_file);
		DP
		cb_exit(data, "MLX FAILED");
		exit(0);
	}
	data->texture.wall_n.addr = mlx_get_data_addr(data->texture.wall_n.mlx_img, &data->texture.wall_n.bpp,
			&data->texture.wall_n.line_len, &data->texture.wall_n.endian);
	data->texture.wall_e.addr = mlx_get_data_addr(data->texture.wall_e.mlx_img, &data->texture.wall_e.bpp,
			&data->texture.wall_e.line_len, &data->texture.wall_e.endian);
	data->texture.wall_s.addr = mlx_get_data_addr(data->texture.wall_s.mlx_img, &data->texture.wall_s.bpp,
			&data->texture.wall_s.line_len, &data->texture.wall_s.endian);
	data->texture.wall_w.addr = mlx_get_data_addr(data->texture.wall_w.mlx_img, &data->texture.wall_w.bpp,
			&data->texture.wall_w.line_len, &data->texture.wall_w.endian);
	if (!data->texture.wall_n.addr || !data->texture.wall_s.addr || !data->texture.wall_e.addr || !data->texture.wall_w.addr)
	{
		DP
		cb_exit(data, "MLX FAILED");
		exit(0);
	}
}

void	init_data2(t_cbdata *data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		data->mini[i].img = NULL;
		data->mini[i].addr = NULL;
		data->mini[i].bits_per_pixel = 0;
		data->mini[i].line_length = 0;
		data->mini[i].endian = 0;
		i++;
	}
	i = 0;
	while (i < 1280)
	{
		data->proj_slic_height[i] = 0;
		data->raycast[i].x = 0;
		data->raycast[i].y = 0;
		data->raycast[i].dist = 0;
		data->raycast[i].wall = 0;
		data->raycast[i].angle = 0.0;
		i++;
	}
	data->texture.wall_n.mlx_img = NULL;
	data->texture.wall_n.addr = NULL;
	data->texture.wall_n.bpp = 0;
	data->texture.wall_n.line_len = 0;
	data->texture.wall_n.endian = 0;
	data->texture.wall_e.mlx_img = NULL;
	data->texture.wall_e.addr = NULL;
	data->texture.wall_e.bpp = 0;
	data->texture.wall_e.line_len = 0;
	data->texture.wall_e.endian = 0;
	data->texture.wall_s.mlx_img = NULL;
	data->texture.wall_s.addr = NULL;
	data->texture.wall_s.bpp = 0;
	data->texture.wall_s.line_len = 0;
	data->texture.wall_s.endian = 0;
	data->texture.wall_w.mlx_img = NULL;
	data->texture.wall_w.addr = NULL;
	data->texture.wall_w.bpp = 0;
	data->texture.wall_w.line_len = 0;
	data->texture.wall_w.endian = 0;
}

void	init_data_keypressed(t_cbdata *data)
{
	int	i;

	i = -1;
	while (++i < 6)
		data->keypressed[i] = 0;
}

void	init_data(t_cbdata *data)
{
	data->map = NULL;
	data->n_file = NULL;
	data->s_file = NULL;
	data->e_file = NULL;
	data->w_file = NULL;
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->ceiling_color = 0;
	data->ceiling_color = 0;
	data->mini_img = 0;
	data->pos_x = 0.0;
	data->pos_y = 0.0;
	data->map_x = 0;
	data->map_y = 0;
	data->angle = 0.0;
	data->redraw = 1;
	init_data2(data);
	init_data_keypressed(data);
}

void	cb_exit(t_cbdata *data, char *err_msg)
{
	if (data->mini[0].img)
		mlx_destroy_image(data->mlx, data->mini[0].img);
	if (data->mini[1].img)
		mlx_destroy_image(data->mlx, data->mini[1].img);
	ft_free_strs(data->map);
	ft_free((void **)&data->e_file);
	ft_free((void **)&data->w_file);
	ft_free((void **)&data->n_file);
	ft_free((void **)&data->s_file);
	if (data->mlx)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		ft_free((void **)&data->mlx);
	}
	if (err_msg)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(err_msg, 2);
		exit(1);
	}
	exit(0);
}
