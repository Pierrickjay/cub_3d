/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:33:14 by pjay              #+#    #+#             */
/*   Updated: 2023/04/06 10:27:46 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	init_data(t_cbdata *data)
{
	int i;

	i = 0;
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
	while (i < 2)
	{
		data->mini[i].img = NULL;
		data->mini[i].addr = NULL;
		data->mini[i].bits_per_pixel = 0;
		data->mini[i].line_length = 0;
		data->mini[i].endian = 0;
		i++;
	}
	data->pos_x = 0;
	data->pos_y = 0;
	data->angle = 0;
	data->redraw = 1;
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
