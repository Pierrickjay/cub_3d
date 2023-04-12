/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:56:00 by pjay              #+#    #+#             */
/*   Updated: 2023/04/12 14:11:50 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

bool	bump_wall(t_cbdata *data, int new_x, int new_y)
{
	// TO DO : check out of range
	new_x /= BLOCK_SIZE;
	new_y /= BLOCK_SIZE;
	if (data->map[new_y][new_x] == '1')
		return (true);
	else
		return (false);
}

void	change_pos_player(t_cbdata *data)
{
	double	new_x;
	double	new_y;
	double	ortho;

	ortho = data->angle + M_PI_2;
	new_x = data->pos_x;
	new_y = data->pos_y;

	if (data->keypressed[up])
	{
		new_x += cos(data->angle);
		new_y -= sin(data->angle);
	}
	if (data->keypressed[down])
	{
		new_x -= cos(data->angle);
		new_y += sin(data->angle);
	}
	if (data->keypressed[left])
	{
		new_x += cos(ortho);
		new_y -= sin(ortho);
	}
	if (data->keypressed[right])
	{
		new_x -= cos(ortho);
		new_y += sin(ortho);
	}
	if (data->keypressed[left_view])
	{
		data->angle = fmod(data->angle + ANGLE_PACE + 2.0 * M_PI, 2.0 * M_PI);
	}
	if (data->keypressed[right_view])
	{
		data->angle = fmod(data->angle - ANGLE_PACE + 2.0 * M_PI, 2.0 * M_PI);
	}
	if (!bump_wall(data, (int)new_x, (int)data->pos_y))
	{
		data->pos_x = new_x;
	}
	if (!bump_wall(data, (int)data->pos_x, (int)new_y))
	{
		data->pos_y = new_y;
	}
}
