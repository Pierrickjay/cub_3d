/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:01:21 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/22 13:54:27 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

t_point	get_endpoint(t_cbdata *data, float angle)
{
	t_point	h_intersect;
	t_point	v_intersect;

	h_intersect = get_h_intersect(data, angle);
	v_intersect = get_v_intersect(data, angle);
	h_intersect.dist = calculate_distance(data, h_intersect);
	v_intersect.dist = calculate_distance(data, v_intersect);
	h_intersect.angle = angle;
	v_intersect.angle = angle;
	if (h_intersect.dist < v_intersect.dist)
		return (h_intersect);
	else
		return (v_intersect);
}

void	minimap_pixel_put(t_cbdata *data, int x, int y, int tile)
{
	int	pxl_x;
	int	pxl_y;

	pxl_x = (x * tile) / BLOCK_SIZE;
	pxl_y = (y * tile) / BLOCK_SIZE;
	my_mlx_pixel_put(data, pxl_x, pxl_y, RAY_COLOR);
}

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

void	draw_lines(t_cbdata *data)
{
	float	angle;
	int		i;

	i = 0;
	while (i < 1280)
	{
		angle = data->angle - atan(((float)i - PLANE_X / 2.0) / (float)PROJ_PLAN);
		angle = fmod(angle + TWO_PI, TWO_PI);
		data->raycast[i] = get_endpoint(data, angle);
		i++;
	}
}
