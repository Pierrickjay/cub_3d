/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:01:21 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/13 11:14:43 by pjay             ###   ########.fr       */
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

	pxl_x = x * tile;
	pxl_x /= BLOCK_SIZE;
	pxl_y = y * tile;
	pxl_y /= BLOCK_SIZE;
	my_mlx_pixel_put(data, pxl_x, pxl_y, RAY_COLOR);
}

void	draw_ray(t_cbdata *data, t_point intersect)
{
	float	slope;
	int		x;
	int		tile;
	float	y;

	tile = data->mini[data->mini_img].mini_tile_size;
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
	angle = data->angle - M_PI / 6.0;
	while (i < 1280)
	{
		angle = fmod(angle + 2.0 * M_PI, 2.0 * M_PI);
		data->raycast[i] = get_endpoint(data, angle);
		if (data->raycast[i].wall == 'N')
			data->raycast[i].y += 1;
		else if (data->raycast[i].wall == 'W')
			data->raycast[i].x += 1;
		draw_ray(data, data->raycast[i]);
		angle = angle + ANGLE_PACE;
		i++;
	}
	//printf("i = %d\n", i);
/*	draw_ray(data, 0.0);
	draw_ray(data, M_PI / 2.0);
	draw_ray(data, M_PI);
	draw_ray(data, M_PI * 2.0 / 3.0);
	draw_ray(data, M_PI * 4.0 / 3.0);
	draw_ray(data, M_PI * 3.0 / 2.0);
	draw_ray(data, M_PI * 5.0 / 3.0);*/
}
