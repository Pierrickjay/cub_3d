/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frexit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:24:40 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/25 16:57:02 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static void	free_texture(t_cbdata *data);

void	cb_exit(t_cbdata *data, char *err_msg)
{
	if (data->image[0].img)
		mlx_destroy_image(data->mlx, data->image[0].img);
	if (data->image[1].img)
		mlx_destroy_image(data->mlx, data->image[1].img);
	ft_free_strs(data->map);
	free_texture(data);
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

static void	free_texture(t_cbdata *data)
{
	int	i;

	i =-1;
	free(data->texture.map.mlx_img);
	while (++i < 4)
	{
		free(data->texture_file[i]);
		data->texture_file[i] = NULL;
		if (data->texture.wall[i].mlx_img)
			mlx_destroy_image(data->mlx, data->texture.wall[i].mlx_img);
		data->texture.wall[i].mlx_img = NULL;
	}
	i = -1;
	while (++i < 32)
	{
		if (data->texture.cats[i].mlx_img)
			mlx_destroy_image(data->mlx, data->texture.cats[i].mlx_img);
		data->texture.cats[i].mlx_img = NULL;
	}
}

