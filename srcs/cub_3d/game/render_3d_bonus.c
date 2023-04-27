/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 10:57:33 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/27 13:41:01 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

static void	set_slice_height(t_cbdata *data);
static void	set_column(t_cbdata *data, t_column *col);

void	render_3d(t_cbdata *data)
{
	int				i;
	t_column		col;
	unsigned int	color;
	float			y;

	set_slice_height(data);
	col.column = -1;
	while (++col.column < PLANE_X)
	{
		set_column(data, &col);
		i = -1;
		while (++i < PLANE_Y)
		{
			if (col.column < MINI_X && i < MINI_Y)
				continue ;
			else if (i < col.top)
				color = data->cf_color[1];
			else if (i <= col.bottom)
			{
				y = BLOCK_SIZE * ((i - PLANE_Y / 2.0) / col.size + 0.5);
				color = img_pix_read(data, (int)y, col.column);
			}
			else
				color = data->cf_color[0];
			my_mlx_pixel_put(data, col.column, i, color);
		}
	}
	put_cat(data);
}

static void	set_column(t_cbdata *data, t_column *col)
{
	col->size = (int)data->proj_slice_height[col->column];
	col->top = (PLANE_Y - col->size) / 2.0;
	col->bottom = (PLANE_Y + col->size) / 2.0;
}

static void	set_slice_height(t_cbdata *data)
{	int		i;
	float	cosinus;

	i = -1;
	while (++i < 1280)
	{
		cosinus = 1.0 / sqrtf(1 + powf(i - PLANE_X / 2.0, 2.0) / powf(PROJ_PLAN, 2.0));
		data->proj_slice_height[i] = (float)PROJ_PLAN  * BLOCK_SIZE\
				/ (data->raycast[i].dist \
				* cosinus);
	}
}
