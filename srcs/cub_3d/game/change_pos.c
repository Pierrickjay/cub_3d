/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:56:00 by pjay              #+#    #+#             */
/*   Updated: 2023/04/06 10:56:13 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

bool	bump_wall(t_cbdata *data, int new_x, int new_y)
{
	new_x /= 64;
	new_y /= 64;
	if (data->map[new_y][new_x] == '1')
		return (true);
	else
		return (false);
}

void	change_pos_player(t_cbdata *data, enum e_keycode move)
{
	int	new_x;
	int	new_y;

	new_x = data->pos_x;
	new_y = data->pos_y;

	if (move == up)
		new_y -= 1;
	else if (move == down)
		new_y += 1;
	else if (move == left)
		new_x -= 1;
	else
		new_x += 1;
	if (!bump_wall(data, new_x, new_y))
	{
		data->pos_x = new_x;
		data->pos_y = new_y;
		data->redraw = 1;
	}
}