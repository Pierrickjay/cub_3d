/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:33:14 by pjay              #+#    #+#             */
/*   Updated: 2023/04/25 17:19:15 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static void	init_null(t_cbdata *data);
static void	init_image(t_cbdata *data);
static void	init_raycast(t_cbdata *data);
static void	init_texture(t_cbdata *data);

void	init_data(t_cbdata *data)
{
	int	i;

	i = -1;
	while (++i < 2)
		data->cf_color[i] = 0;
	i = -1;
	while (++i < 6)
		data->keypressed[i] = 0;
	i = -1;
	while (++i < 4)
		data->texture_file[i] = NULL;
	init_null(data);
	init_image(data);
	init_raycast(data);
	init_texture(data);
}

static void	init_null(t_cbdata *data)
{
	int	i;

	i = -1;
	data->map = NULL;
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->cats = NULL;
	data->img = 0;
	data->pos_x = 0.0;
	data->pos_y = 0.0;
	data->map_x = 0;
	data->map_y = 0;
	data->angle = 0.0;
	while (++i < 6)
		data->keypressed[i] = 0;
}

void	init_image(t_cbdata *data)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		data->image[i].img = NULL;
		data->image[i].addr = NULL;
		data->image[i].bits_per_pixel = 0;
		data->image[i].line_length = 0;
		data->image[i].endian = 0;
	}
}

static void	init_raycast(t_cbdata *data)
{
	int	i;

	i = -1;
	while (++i < 1280)
	{
		data->proj_slice_height[i] = 0;
		data->raycast[i].x = 0;
		data->raycast[i].y = 0;
		data->raycast[i].dist = 0;
		data->raycast[i].wall = 0;
		data->raycast[i].angle = 0.0;
	}
}

static void	init_texture(t_cbdata *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		data->texture.wall[i].mlx_img = NULL;
		data->texture.wall[i].addr = NULL;
		data->texture.wall[i].bpp = 0;
		data->texture.wall[i].line_len = 0;
		data->texture.wall[i].endian = 0;
	}
	i = -1;
	while (++i < 32)
	{
		data->texture.cat[i].mlx_img = NULL;
		data->texture.cat[i].addr = NULL;
		data->texture.cat[i].bpp = 0;
		data->texture.cat[i].line_len = 0;
		data->texture.cat[i].endian = 0;
		data->texture.cat[i].pos_y = 0.0;
		data->texture.cat[i].pos_x = 0.0;
	}
	data->texture.map.mlx_img = NULL;
	data->texture.map.addr = NULL;
	data->texture.map.bpp = 0;
	data->texture.map.line_len = 0;
	data->texture.map.endian = 0;
}
