/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:25:32 by pjay              #+#    #+#             */
/*   Updated: 2023/04/18 14:02:44 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	render_3d(t_cbdata *data)
{
 	int				i;
	unsigned int	color;
	int				column;
	float			size_to_print;
	float			top_y;
	float			bottom_y;
	int				j;

	size_to_print = 0;
	i = 0;
	while (i < 1280)
	{
		data->proj_slice_height[i] = (float)BLOCK_SIZE \
				/ (data->raycast[i].dist \
				* cos(data->angle - data->raycast[i].angle)) * PROJ_PLAN;
		i++;
	}
	i = 0;
	column = 0;
	while (column < PLANE_X) 
	{
		size_to_print = data->proj_slice_height[column]; 
		top_y = (float)PLANE_Y / 2.0 - size_to_print / 2.0;
		bottom_y = (float)top_y + size_to_print;
		if (top_y < 0)
			top_y = 0;
		j = top_y;
		i = bottom_y;
		while (top_y <= bottom_y && top_y <= PLANE_Y)
		{
			if (data->raycast[column].wall == n)
			{
				color = img_pix_read(&data->texture.wall[n], 1.0 - (float)(bottom_y - top_y) / size_to_print, data, column);
			}
			else if (data->raycast[column].wall == s)
			{
				color = img_pix_read(&data->texture.wall[s], 1.0 - (float)(bottom_y - top_y) / size_to_print, data, column);
			}
			else if (data->raycast[column].wall == e)
			{
				color = img_pix_read(&data->texture.wall[e], 1.0 - (float)(bottom_y - top_y) / size_to_print, data, column);
			}
			else
			{
				color = img_pix_read(&data->texture.wall[w], 1.0 - (float)(bottom_y - top_y) / size_to_print, data, column);
			}
			if (!(column < 320 && top_y < 200))
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
			if (!(column < 320 && j < 200))
				my_mlx_pixel_put(data, column, j, data->cf_color[1]);
			j--;
		}
		column++;
	}
}
