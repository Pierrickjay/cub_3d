/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pos_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:33:35 by pjay              #+#    #+#             */
/*   Updated: 2023/05/01 09:33:36 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

bool	bump_wall(t_cbdata *data, int new_x, int new_y)
{
	new_x /= BLOCK_SIZE;
	new_y /= BLOCK_SIZE;
	if (cell_isa(data->map[new_y][new_x], CELL_HARD_BONUS))
		return (true);
	else
		return (false);
}

void	reset_new_pos(t_point *new_pos, float value, float angle)
{
	new_pos->x -= 3 * value * cos(angle);
	new_pos->y += 3 * value * sin(angle);
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

// mickey stands for mouse index celerity key
void	change_view_player(t_cbdata *data)
{
	int		mickey;
	float	speed[6];

	speed[down] = 0.0;
	speed[right] = 0.0;
	speed[little_right_view] = 16.0;
	speed[half_right_view] = 25.0;
	speed[mouse_right] = 40.0;
	speed[right_view] = 20.0;
	mickey = 1;
	while (++mickey < 6)
	{
		if (data->keypressed[mickey])
		{
			data->angle = fmod(data->angle - data->keypressed[mickey] * \
					speed[mickey] * ANGLE_PACE + TWO_PI, TWO_PI);
		}
	}
}
