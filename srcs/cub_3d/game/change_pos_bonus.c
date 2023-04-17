/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pos_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:33:35 by pjay              #+#    #+#             */
/*   Updated: 2023/04/17 15:46:43 by pjay             ###   ########.fr       */
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

void	reset_new_pos(t_point *new_pos, float value, float angle)
{
	new_pos->x -= 2 * value * cos(angle);
	new_pos->y += 2 * value * sin(angle);
}

void	change_pos_player(t_cbdata *data)
{
	t_point	new_pos;

	new_pos.x = data->pos_x;
	new_pos.y = data->pos_y;
	if (data->keypressed[down])
		reset_new_pos(&new_pos, data->keypressed[down], data->angle);
	if (data->keypressed[right])
		reset_new_pos(&new_pos, data->keypressed[right], data->angle + M_PI_2);
	if (!bump_wall(data, (int)new_pos.x, (int)data->pos_y))
		data->pos_x = new_pos.x;
	if (!bump_wall(data, (int)data->pos_x, (int)new_pos.y))
		data->pos_y = new_pos.y;
}

void	change_view_player(t_cbdata *data)
{
	if (data->keypressed[right_view])
	{
		//DP
		data->angle = fmod(data->angle - data->keypressed[right_view] * 16.0 * \
				ANGLE_PACE + 2.0 * M_PI, 2.0 * M_PI);
	}
	else if (data->keypressed[mouse_right])
	{
		//DP
		data->angle = fmod(data->angle - data->keypressed[mouse_right] * 40.0 * \
				ANGLE_PACE + 2.0 * M_PI, 2.0 * M_PI);
		//data->keypressed[mouse_right] = 0;
	}
	else if (data->keypressed[little_right_view])
	{
		//DP
		data->angle = fmod(data->angle - data->keypressed[little_right_view] * 16.0 * \
				ANGLE_PACE + 2.0 * M_PI, 2.0 * M_PI);
		//data->keypressed[little_right_view] = 0;
	}
	else if (data->keypressed[half_right_view])
	{
		//DP
		data->angle = fmod(data->angle - data->keypressed[half_right_view] * 25.0 * \
				ANGLE_PACE + 2.0 * M_PI, 2.0 * M_PI);
		//data->keypressed[half_right_view] = 0;
	}
	//mlx_mouse_move(data->mlx, data->mlx_win, PLANE_X / 2, PLANE_Y / 2);
}
