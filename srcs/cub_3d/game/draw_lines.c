/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:01:21 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/06 16:07:56 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"




t_point	get_h_intersect(t_cbdata *data, double angle)
{
	int		int_val;		
	t_point	offset;
	t_point	pointA;
	//t_point	intersect;

	int_val =  data->pos_y - data->pos_y % BLOCK_SIZE;
	pointA.y = (double)int_val;
	offset.y = BLOCK_SIZE;
	if (angle < M_PI)
		offset.y *= -1;
	else
		pointA.y += BLOCK_SIZE;
	offset.x = offset.y / tan(angle);
	pointA.x = (double)data->pos_x + ((double)data->pos_y - pointA.y) / tan(angle);
	while (1)
	{
		if (data->map[((int)pointA.y + (int)offset.y /  2 )/ BLOCK_SIZE][(int)pointA.x / BLOCK_SIZE] == '1')
			return ( pointA);
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

	intersect = get_endpoint(data, angle);
	printf("intersect: %f %f\n",  intersect.x, intersect.y);
}

void	draw_lines(t_cbdata *data)
{
	draw_ray(data, M_PI / 3);
}

	/*
	intersect.y = ;
	if (angle < ANGLE_PACE && angle > -1 * ANGLE_PACE)
	{
		 intersect.x = INFINITY;

	}
	else if (angle > M_PI_2 - ANGLE_PACE && angle < M_PI_2 + ANGLE_PACE)
	{
		intersect.x = (double)cbdata->pos_x;
	}
	else if (angle > -1 * M_PI_2 - ANGLE_PACE && angle < -1 * M_PI_2 + ANGLE_PACE)
	{
		intersect.x = (double)cbdata->pos_x;
	}
	tmp = tan(angle);
	if (errno == FE_OVERFLOW)
		Xa_offset = 0;*/
