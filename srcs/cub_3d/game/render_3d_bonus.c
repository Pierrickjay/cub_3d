/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 10:57:33 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/28 10:02:49 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

static void	set_slice_height(t_cbdata *data);
static void	set_column(t_cbdata *data, t_column *col);
//static void	put_string_to_window(t_cbdata *data);
static int	draw_or_not(t_cbdata *data, int x, int i);

void	render_3d(t_cbdata *data)
{
	int				i;
	t_column		col;
	unsigned int	color;

	set_slice_height(data);
	col.column = -1;
	while (++col.column < PLANE_X)
	{
		set_column(data, &col);
		i = -1;
		while (++i < PLANE_Y)
		{
			if (draw_or_not(data, col.column, i) == 0)
				continue ;
			else if (i < col.top)
				color = data->cf_color[1];
			else if (i <= col.bottom)
				color = img_pix_read(data, (BLOCK_SIZE * (i - col.top)) \
						/ col.size, col.column);
			else
				color = data->cf_color[0];
			my_mlx_pixel_put(data, col.column, i, color);
		}
	}
}

static void	set_column(t_cbdata *data, t_column *col)
{
	col->size = (int)data->proj_slice_height[col->column];
	col->top = (PLANE_Y - col->size) / 2;
	col->bottom = col->top + col->size;
}

static void	set_slice_height(t_cbdata *data)
{
	int	i;

	i = -1;
	while (++i < 1280)
		data->proj_slice_height[i] = (float)BLOCK_SIZE * PROJ_PLAN \
				/ (data->raycast[i].dist \
				* cos(data->angle - data->raycast[i].angle));
}

static int	draw_or_not(t_cbdata *data, int x, int y)
{
	if ((x < MINI_X && y < MINI_Y) \
				|| (x > PLANE_X - (64 * data->digits) && y < 64) || \
				(x > PLANE_X - (64 * data->digits_all) && y < 128 && y > 64))
		return (0);
	else
		return (1);
}
