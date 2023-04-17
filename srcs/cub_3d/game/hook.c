/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:18:23 by pjay              #+#    #+#             */
/*   Updated: 2023/04/17 09:11:22 by pjay             ###   ########.fr       */
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
	else if (keycode == KEY_LEFT)
		data->keypressed[right_view] = -1 * value;
	else if (keycode == KEY_RIGHT)
		data->keypressed[right_view] = value;
	//data->redraw = 1;
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

void	set_hooks(t_cbdata *data)
{
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &key_press_hook, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, \
			&key_release_hook, data);
	mlx_hook(data->mlx_win, 17, 0, &exit_hook, data);
}
