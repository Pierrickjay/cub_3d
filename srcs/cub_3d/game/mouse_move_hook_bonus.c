/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_hook_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:59:16 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/18 11:33:27 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

//mickey stands for mouse index celerity key

static int	catch_mickey(int slice);

int	mouse_move_hook(int x, int y, t_cbdata *data)
{
	int	slice;
	int	mickey;

	mlx_mouse_get_pos(data->mlx, data->mlx_win, &x, &y);
	slice = 8 * x / PLANE_X;
	mouse_move_hook_out(x, y, data);
	mickey = catch_mickey(slice);
	if (mickey)
		set_move_player(data, mickey, 1);
	return (0);
}

int	mouse_move_hook_out(int x, int y, t_cbdata *data)
{
	(void)x;
	(void)y;
	data->keypressed[little_right_view] = 0;
	data->keypressed[half_right_view] = 0;
	data->keypressed[mouse_right] = 0;
	return (0);
}

static int	catch_mickey(int slice)
{
	int	mickey_mouse[8];

	mickey_mouse[0] = MOUSE_LEFT;
	mickey_mouse[1] = HALF_LEFT;
	mickey_mouse[2] = LITTLE_LEFT;
	mickey_mouse[3] = MOUSE_CENTER;
	mickey_mouse[4] = MOUSE_CENTER;
	mickey_mouse[5] = LITTLE_RIGHT;
	mickey_mouse[6] = HALF_RIGHT;
	mickey_mouse[7] = MOUSE_RIGHT;
	if (slice >= 0 && slice <= 7)
		return (mickey_mouse[slice]);
	return (MOUSE_RIGHT);
}
