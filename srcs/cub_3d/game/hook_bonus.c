/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:54:34 by pjay              #+#    #+#             */
/*   Updated: 2023/04/18 11:34:45 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

static int	key_press_hook(int keycode, t_cbdata *data);
static int	key_release_hook(int keycode, t_cbdata *data);
static int	exit_hook(t_cbdata *data);

void	set_hooks(t_cbdata *data)
{
	mlx_hook(data->mlx_win, MotionNotify, PointerMotionMask, \
			&mouse_move_hook, data);
	mlx_hook(data->mlx_win, LeaveNotify, PointerMotionMask, \
			&mouse_move_hook_out, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, \
			&key_press_hook, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, \
			&key_release_hook, data);
	mlx_hook(data->mlx_win, 17, 0, &exit_hook, data);
}

static int	key_press_hook(int keycode, t_cbdata *data)
{
	if (keycode == XK_Escape)
		cb_exit(data, NULL);
	set_move_player(data, keycode, 1);
	return (0);
}

static int	key_release_hook(int keycode, t_cbdata *data)
{
	if (keycode == XK_Escape)
		cb_exit(data, NULL);
	set_move_player(data, keycode, 0);
	return (0);
}

static int	exit_hook(t_cbdata *data)
{
	cb_exit(data, NULL);
	return (0);
}
