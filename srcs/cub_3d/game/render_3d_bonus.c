/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 10:57:33 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/26 11:55:35 by pjay             ###   ########.fr       */
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
				color = img_pix_read(data, (BLOCK_SIZE * (i - col.top)) \
						/ col.size, col.column);
			else
				color = data->cf_color[0];
			my_mlx_pixel_put(data, col.column, i, color);
		}
	}
	arrange_cats_list(data);
	//put_cat(data);
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
