/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_intersect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:32:50 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/10 12:05:52 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static bool	special_value(t_point *pointA, double cot);
static void	set_pointA(t_cbdata *data, t_point *pointA, double angle);
static void	set_offset(t_point *offset, double angle);
static int	next_pointA(t_cbdata *data, t_point *pointA, t_point offset, double angle);

t_point	get_h_intersect(t_cbdata *data, double angle)
{
	int		found;
	double	cot;
	t_point	offset;
	t_point	pointA;

	cot = 1 / tan(angle);
	printf("angle is %f an cot is %f\n", angle, cot);
	if (special_value(&pointA, cot))
		return (pointA);
	set_pointA(data, &pointA, angle);
	set_offset(&offset, angle);

	found = 0;
	while (!found)
		found = next_pointA(data, &pointA, offset, angle);
	DP
	return (pointA);
}

static bool	special_value(t_point *pointA, double cot)
{
	int	class;

	class = fpclassify(cot);
	if (class == FP_INFINITE)
	{
		pointA->x = INFINITY;
		pointA->y = INFINITY;
		return (true);
	}
	return (false);
}

static void	set_pointA(t_cbdata *data, t_point *pointA, double angle)
{
	pointA->y = (double)(data->pos_y - data->pos_y % BLOCK_SIZE);
	if (angle > M_PI)
		pointA->y += BLOCK_SIZE;
	pointA->x = (double)data->pos_x - ((double)data->pos_y - pointA->y) / tan(angle);
	printf("pointA in set is %f %f\n", pointA->x, pointA->y);
}

static void	set_offset(t_point *offset, double angle)
{
	if (angle > M_PI)
		offset->y = BLOCK_SIZE;
	else
		offset->y = -BLOCK_SIZE;
	offset->x = offset->y / tan(angle);
}

static int	next_pointA(t_cbdata *data, t_point *pointA, t_point offset, double angle)
{
	int 	x;
	int		y;
	int		delta;

	if (angle < M_PI)
		delta = -3;
	else
		delta = 3;
	DP
	if (point_outofrange(pointA))
		return (1);
	DP
	x = ((int)pointA->x) / BLOCK_SIZE;
	y = ((int)pointA->y + delta)/ BLOCK_SIZE;
	if (data->map[y][x] == '1')
		return (1);
	printf("pointA in next is %f %f\n", pointA->x, pointA->y);
	pointA->x += offset.x;
	pointA->y += offset.y;
	return (0);
}
