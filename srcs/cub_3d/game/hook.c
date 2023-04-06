/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:18:23 by pjay              #+#    #+#             */
/*   Updated: 2023/04/06 10:56:52 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	set_move_player(t_cbdata *data, int keycode)
{
	if (keycode == 119 || keycode == 65362)
		change_pos_player(data, up);
	if (keycode == 115 || keycode == 65364)
		change_pos_player(data, down);
	if (keycode == 97 || keycode == 65361)
		change_pos_player(data, left);
	if (keycode == 100 || keycode == 65363)
		change_pos_player(data, right);
	printf("pos_x = %d pos_y =%d tile_size = %d \n", data->pos_x, data->pos_y, data->mini[0].mini_tile_size);
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
	mlx_key_hook(data->mlx_win, &key_press_hook, data);
	mlx_hook(data->mlx_win, 17, 0, &exit_hook, data);
}
