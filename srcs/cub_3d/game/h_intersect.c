/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_intersect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:32:50 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/11 15:07:34 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static bool	special_value(t_point *pointA, double cot);
static void	set_pointA(t_cbdata *data, t_point *pointA, double angle, double cot);
static void	set_offset(t_point *offset, double angle, double cot);
static int	next_pointA(t_cbdata *data, t_point *pointA, t_point offset, double angle);

t_point	get_h_intersect(t_cbdata *data, double angle)
{
	int		found;
	double	cot;
	t_point	offset;
	t_point	pointA;

	if (angle > M_PI)
		pointA.wall = 'S';
	else
		pointA.wall = 'N';
	cot = 1.0 / tan(angle);
	if (special_value(&pointA, cot))
		return (pointA);
	set_pointA(data, &pointA, angle, cot);
	set_offset(&offset, angle, cot);
	found = 0;
	while (!found)
		found = next_pointA(data, &pointA, offset, angle);
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

static void	set_pointA(t_cbdata *data, t_point *pointA, double angle, double cot)
{
	pointA->y = (double)(data->pos_y - data->pos_y % BLOCK_SIZE);
	if (angle > M_PI)
		pointA->y += BLOCK_SIZE;
	else
		pointA->y -= 1;
	pointA->x = (double)data->pos_x + ((double)data->pos_y - pointA->y) * cot;
}

static void	set_offset(t_point *offset, double angle, double cot)
{
	if (angle < M_PI)
	{
		offset->y = - BLOCK_SIZE;
		offset->x = BLOCK_SIZE * cot;
	}
	else
	{
		offset->y = BLOCK_SIZE;
		offset->x = -1.0 * BLOCK_SIZE * cot;
	}
}

static int	next_pointA(t_cbdata *data, t_point *pointA, t_point offset, double angle)
{
	int 	x;
	int		y;

	(void)angle;
	if (point_outofrange(data, pointA))
		return (1);
	x = ((int)pointA->x) / BLOCK_SIZE;
	y = ((int)pointA->y)/ BLOCK_SIZE;
	if (data->map[y][x] == '1')
		return (1);
	pointA->x += offset.x;
	pointA->y += offset.y;
	return (0);
}
