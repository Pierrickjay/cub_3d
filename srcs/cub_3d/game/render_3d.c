/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:11:31 by pjay              #+#    #+#             */
/*   Updated: 2023/04/18 14:03:50 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static void	set_slice_height(t_cbdata *data);
static unsigned int	get_wall_color(t_cbdata *data, float sc_y, int column);

void	render_3d(t_cbdata *data)
{
 	int				i;
	int				j;
	int				column;
	unsigned int	color;
	float			size_to_print;
	float			top_y;
	float			bottom_y;

	i = 0;
	column = 0;
	set_slice_height(data);
	while (column < PLANE_X) 
	{
		size_to_print = data->proj_slice_height[column]; 
		top_y = ((float)PLANE_Y - size_to_print) / 2.0;
		bottom_y = top_y + size_to_print;
		if (top_y < 0)
			top_y = 0;
		j = top_y;
		i = bottom_y;
		while (top_y <= bottom_y && top_y <= PLANE_Y)
		{
			color = get_wall_color(data, 1.0 - (float)(bottom_y - top_y) / size_to_print, column);
			my_mlx_pixel_put(data, column, top_y, color);
			top_y++;
		}
		while (i < 800)
		{
			my_mlx_pixel_put(data, column, i, data->cf_color[0]);
			i++;
		}
		while (j >= 0 && top_y < PLANE_Y)
		{
			my_mlx_pixel_put(data, column, j, data->cf_color[1]);
			j--;
		}
		column++;
	}
}

static void	set_slice_height(t_cbdata *data)
{
	int	i;

	i = -1;
	while (++i < 1280)
		data->proj_slice_height[i] = (float)BLOCK_SIZE * PROJ_PLAN \
				/ (data->raycast[i].dist \
				* cos(data->angle - data->raycast[i].angle));
}

static unsigned int	get_wall_color(t_cbdata *data, float sc_y, int column)
{
	int	color;

	if (data->raycast[column].wall == n) 
	{
		color = img_pix_read(&data->texture.wall[n], sc_y, data, column);
	}
	else if (data->raycast[column].wall == s) 
	{
		color = img_pix_read(&data->texture.wall[s], sc_y, data, column);
	}
	else if (data->raycast[column].wall == e) 
	{
		color = img_pix_read(&data->texture.wall[e], sc_y, data, column);
	}
	else 
	{
		color = img_pix_read(&data->texture.wall[w], sc_y, data, column);
	}
	return (color);
}
