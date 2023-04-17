/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:54:34 by pjay              #+#    #+#             */
/*   Updated: 2023/04/17 17:51:44 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	set_move_player(t_cbdata *data, int keycode, int value)
{
	if (keycode == KEY_W)
		data->keypressed[down] = -1 * value;
	else if (keycode == KEY_S)
		data->keypressed[down] = value;
	else if (keycode == KEY_A)
		data->keypressed[right] = -1 * value;
	else if (keycode == KEY_D)
		data->keypressed[right] = value;
	else if (keycode == LITTLE_RIGHT)
		data->keypressed[little_right_view] = value;
	else if (keycode == HALF_RIGHT)
		data->keypressed[half_right_view] = value;
	else if (keycode == MOUSE_RIGHT)
		data->keypressed[mouse_right] = value;
	else if (keycode == KEY_RIGHT)
		data->keypressed[right_view] = value;
	else if (keycode == LITTLE_LEFT)
		data->keypressed[little_right_view] = -1 * value;
	else if (keycode == HALF_LEFT)
		data->keypressed[half_right_view] = -1 * value;
	else if (keycode == MOUSE_LEFT)
		data->keypressed[mouse_right] = -1 * value ;
	else if (keycode == KEY_LEFT)
		data->keypressed[right_view] = -1 * value;
}

int	key_press_hook(int keycode, t_cbdata *data)
{
	if (keycode == XK_Escape)
		cb_exit(data, NULL);
	set_move_player(data, keycode, 1);
	return (0);
}

int	key_release_hook(int keycode, t_cbdata *data)
{
	if (keycode == XK_Escape)
		cb_exit(data, NULL);
	set_move_player(data, keycode, 0);
	return (0);
}

int	exit_hook(t_cbdata *data)
{
	cb_exit(data, NULL);
	return (0);
}

int	mouse_moove_hook(int x, int y, t_cbdata *data)
{
	int plane_2;

	plane_2 = PLANE_X / 2;
	mlx_mouse_get_pos(data->mlx, data->mlx_win, &x, &y);
	if (x > plane_2)
	{
		if (x > (plane_2) + (plane_2 / 4 * 3))
		{

			data->keypressed[half_right_view] = 0;
			data->keypressed[little_right_view] = 0;
			set_move_player(data, MOUSE_RIGHT, 1);
		}
		else if (x > (plane_2) + (plane_2 / 4 * 2))
		{
			set_move_player(data, HALF_RIGHT, 1);
			data->keypressed[mouse_right] = 0;
			data->keypressed[little_right_view] = 0;
		}
		else if (x > (plane_2) + (plane_2 / 4))
		{
			set_move_player(data, LITTLE_RIGHT, 1);
			data->keypressed[half_right_view] = 0;
			data->keypressed[mouse_right] = 0;
		}
		else if (x > (plane_2))
		{
			data->keypressed[little_right_view] = 0;
			data->keypressed[half_right_view] = 0;
			data->keypressed[mouse_right] = 0;
		}
	}
	else
	{
		if (x < (plane_2) - (plane_2 / 4 * 3))
		{
			data->keypressed[little_right_view] = 0;
			data->keypressed[half_right_view] = 0;
			set_move_player(data, MOUSE_LEFT, 1);
		}
		else if (x < (plane_2) - (plane_2 / 4 * 2))
		{
			data->keypressed[little_right_view] = 0;
			data->keypressed[mouse_right] = 0;
			set_move_player(data, HALF_LEFT, 1);
		}
		else if (x < (plane_2) - (plane_2 / 4))
		{
			data->keypressed[half_right_view] = 0;
			data->keypressed[mouse_right] = 0;
			set_move_player(data, LITTLE_LEFT, 1);
		}
		else
		{
			data->keypressed[little_right_view] = 0;
			data->keypressed[half_right_view] = 0;
			data->keypressed[mouse_right] = 0;
		}
	}
	return (0);
}

int	mouse_moove_hook_out(int x, int y, t_cbdata *data)
{
	(void)x;
	(void)y;
	DP
	data->keypressed[little_right_view] = 0;
	data->keypressed[half_right_view] = 0;
	data->keypressed[right_view] = 0;
	return (0);

}

void	set_hooks(t_cbdata *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	mlx_hook(data->mlx_win, MotionNotify, PointerMotionMask, &mouse_moove_hook, data);
	mlx_hook(data->mlx_win, LeaveNotify, PointerMotionMask, &mouse_moove_hook_out, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &key_press_hook, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, \
			&key_release_hook, data);
	mlx_hook(data->mlx_win, 17, 0, &exit_hook, data);
}
