/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:24:50 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/25 17:38:12 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	draw_ray(t_cbdata *data, t_point intersect)
{
	float	slope;
	int		x;
	int		tile;
	float	y;

	tile = data->image[data->img].mini_tile_size;
	if (tile == 0)
		tile = 1;
	if (isinf(intersect.x) || isinf(intersect.y))
		return ;
	slope = (intersect.y - data->pos_y) / (intersect.x - data->pos_x);
	x = (int)data->pos_x;
	y = data->pos_y;
	if (isinf(slope) == -1)
	{
		while (y >= (int)intersect.y)
		{
			minimap_pixel_put(data, x, (int)y, tile);
			y--;
		}
	}
	if (isinf(slope) == 1)
	{
		while (y <= (int)intersect.y)
		{
			minimap_pixel_put(data, x, (int)y, tile);
			y++;
		}
	}
	else if (intersect.x > data->pos_x)
	{
		while (x < (int)intersect.x)
		{
			minimap_pixel_put(data, x, (int)y, tile);
			x++;
			y += slope;
		}
	}
	else
	{
		while (x > (int)intersect.x)
		{
			minimap_pixel_put(data, x, (int)y, tile);
			x--;
			y -= slope;
		}
	}
}
