/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_intersect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:48:16 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/11 15:08:46 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static bool	special_value(t_point *pointB, double tangente);
static void	set_pointB(t_cbdata *data, t_point *pointB, double angle, double tangente);
static void	set_offset(t_point *offset, double angle, double tangente);
static int	next_pointB(t_cbdata *data, t_point *pointB, t_point offset, double angle);

t_point	get_v_intersect(t_cbdata *data, double angle)
{
	int		found;
	double	tangente;
	t_point	offset;
	t_point	pointB;

	if (angle < M_PI / 2.0 || angle > 3.0 / 2.0 * M_PI)
		pointB.wall = 'E';
	else
		pointB.wall = 'W';
	tangente = tan(angle);
	if (special_value(&pointB, tangente))
		return (pointB);
	set_pointB(data, &pointB, angle, tangente);
	set_offset(&offset, angle, tangente);
	found = 0;
	while (!found)
		found = next_pointB(data, &pointB, offset, angle);
	return (pointB);
}

static bool	special_value(t_point *pointB, double tangente)
{
	int	class;

	class = fpclassify(tangente);
	if (class == FP_INFINITE)
	{
		pointB->x = INFINITY;
		pointB->y = INFINITY;
		return (true);
	}
	return (false);
}

static void	set_pointB(t_cbdata *data, t_point *pointB, double angle, double tangente)
{
	pointB->x = (double)(data->pos_x - data->pos_x % BLOCK_SIZE);
	if (angle < M_PI / 2.0 || angle > 3.0 / 2.0 * M_PI)
		pointB->x += BLOCK_SIZE;
	else
		pointB->x -= 1.0;
	pointB->y = (double)data->pos_y + ((double)data->pos_x - pointB->x) * tangente;
}

static void	set_offset(t_point *offset, double angle, double tangente)
{
	if (angle < M_PI / 2.0 || angle > 3.0 / 2.0 * M_PI)
	{
		offset->x =  BLOCK_SIZE;
		offset->y = -1.0* offset->x * tangente;
	}
	else
	{
		offset->x = - BLOCK_SIZE;
		offset->y = -1.0 * offset->x * tangente;
	}
}

static int	next_pointB(t_cbdata *data, t_point *pointB, t_point offset, double angle)
{
	int 	x;
	int		y;

	(void)angle;
	if (point_outofrange(data, pointB))
		return (1);
	x = ((int)pointB->x) / BLOCK_SIZE;
	y = ((int)pointB->y)/ BLOCK_SIZE;
	if (data->map[y][x] == '1')
		return (1);
	pointB->x += offset.x;
	pointB->y += offset.y;
	return (0);
}