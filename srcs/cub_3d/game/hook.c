/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:18:23 by pjay              #+#    #+#             *//*   Updated: 2023/04/11 14:56:47 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	set_move_player(t_cbdata *data, int keycode)
{
	if (keycode == KEY_W)
		change_pos_player(data, up);
	else if (keycode == KEY_S)
		change_pos_player(data, down);
	else if (keycode == KEY_A)
		change_pos_player(data, left);
	else if (keycode == KEY_D)
		change_pos_player(data, right);
	else if (keycode == KEY_LEFT)
		change_pos_player(data, left_view);
	else if (keycode == KEY_RIGHT)
		change_pos_player(data, right_view);
}

int	key_press_hook(int keycode, t_cbdata *data)
{
	if (keycode == XK_Escape)
		cb_exit(data, NULL);
	if (keycode == 119 || keycode == 65362 || keycode == 115 || keycode == 65364
		|| keycode == 97 || keycode == 65361 || keycode == 100
		|| keycode == 65363)
		set_move_player(data, keycode);
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
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, &key_press_hook, data);
	mlx_hook(data->mlx_win, 17, 0, &exit_hook, data);
}
