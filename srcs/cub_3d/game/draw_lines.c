/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:01:21 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/06 18:43:02 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

t_point	get_h_intersect(t_cbdata *data, double angle)
{
	int		int_val;		
	t_point	offset;
	t_point	pointA;
	int 	x;
	int		y;
	//t_point	intersect;

	int_val =  data->pos_y - data->pos_y % BLOCK_SIZE;
	pointA.y = (double)int_val;
	offset.y = BLOCK_SIZE;
	if (angle < M_PI)
		offset.y *= -1;
	else
		pointA.y += BLOCK_SIZE;
	offset.x = offset.y / tan(angle);
	pointA.x = (double)data->pos_x - ((double)data->pos_y - pointA.y) / tan(angle);
	while (1)
	{
		x = ((int)pointA.x) / BLOCK_SIZE;
		y = ((int)pointA.y - 9)/ BLOCK_SIZE;
		if (data->map[y][x] == '1')
		{
			printf("intersected block is x: %d y: %d\n", x, y); 
			return ( pointA);
		}
		pointA.x += offset.x;
		pointA.y += offset.y;
	}
}

t_point	get_endpoint(t_cbdata *data, double angle)
{
	t_point	h_intersect;
	//t_point	v_intersect;
	//float	h_distance;
	//float	v_distance;

	h_intersect = get_h_intersect(data, angle);
	//v_intersect = get_v_intersect(data, angle);
	//h_distance = calculate_distance(data, h_intersect);
	//v_distance = calculate_distance(data, v_intersect);
	
	//if (h_distance < v_distance)
		return (h_intersect);
	//else
	//	return (v_intersect);
}

void	draw_ray(t_cbdata *data, double	angle)
{
	t_point	intersect;
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
	intersect = get_endpoint(data, angle);
	slope = (intersect.y - (double)data->pos_y) / (intersect.x - (double)data->pos_x);
	x = data->pos_x;
	y = data->pos_y;
	if (intersect.x > (double)data->pos_x)
	{
		while (x <= (int)intersect.x)
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
		while (x >= (int)intersect.x)
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
	printf("intersect: %f %f\n",  intersect.x, intersect.y);
}

void	draw_lines(t_cbdata *data)
{
	draw_ray(data, M_PI / 3);
}
