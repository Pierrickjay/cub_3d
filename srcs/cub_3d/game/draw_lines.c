/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:01:21 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/12 15:34:20 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"


t_point	get_endpoint(t_cbdata *data, double angle)
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
void	draw_ray(t_cbdata *data, t_point intersect)
{
	double	slope;
	int		color;
	int		x;
	int		tile;
	int		print_x;
	int		print_y;
	float	y;

	color = 0xFFFF84;
	tile = data->mini[data->mini_img].mini_tile_size;
	if (tile == 0)
		tile = 1;
	//intersect = get_endpoint(data, angle);
	//printf("Intersect: x: %f, y: %f, dist: %f, wall: %c\n", intersect.x, intersect.y, intersect.dist, intersect.wall);
	if (isinf(intersect.x) || isinf(intersect.y))
		return ;
	slope = (intersect.y - data->pos_y) / (intersect.x - data->pos_x);
	x = (int)data->pos_x;
	y = data->pos_y;
	if (isinf(slope) == -1)
	{
		print_x = x * tile;
		print_x /= 64;
		while (y >= (int)intersect.y)
		{
			print_y = y * tile;
			print_y /= 64;
			my_mlx_pixel_put(data, print_x, print_y, color);
			y--;
		}
	}
	if (isinf(slope) == 1)
	{
		print_x = x * tile;
		print_x /= 64;
		while (y <= (int)intersect.y)
		{
			print_y = y * tile;
			print_y /= 64;
			my_mlx_pixel_put(data, print_x, print_y, color);
			y++;
		}
	}
	else if (intersect.x > data->pos_x)
	{
		while (x < (int)intersect.x)
		{
			print_x = x * tile;
			print_x /= 64;
			print_y = (int)y * tile;
			print_y /= 64;
			my_mlx_pixel_put(data, print_x, print_y, color);
			x++;
			y += slope;
		}
	}
	else
	{
		while (x > (int)intersect.x)
		{
			print_x = x * tile;
			print_x /= 64;
			print_y = (int)y * tile;
			print_y /= 64;
			my_mlx_pixel_put(data, print_x, print_y, color);
			x--;
			y -= slope;
		}
	}
}

void	draw_lines(t_cbdata *data)
{
	double	angle;
	int		i;

	i = 0;
	angle = data->angle - M_PI / 6.0;

	while (i < 1280)
	{
		angle = fmod(angle + 2.0 * M_PI, 2.0 * M_PI);
		data->raycast[i] = get_endpoint(data, angle);
	//	draw_ray(data, data->raycast[i]);
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

