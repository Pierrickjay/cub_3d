/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:23:53 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/04 12:43:11 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

int	key_pressed(int keycode, void *void_data)
{
	static int	old_key = 0;
	t_cbdata	*data;

	data = void_data;
	if (S == keycode)
		view_pos_set(data, 0, 1);
	else if (W == keycode)
		view_pos_set(data, 0, -1);
	else if (D == keycode)
		view_pos_set(data, 1, 0);
	else if (A == keycode)
		view_pos_set(data, -1, 0);
	return (1);
}

int	key_released(int keycode, void *void_data)
{
	t_cbdata	*data;

	data = void_data;
	if (ESCAPE == keycode)
		game_exit(data, NULL);
	if (view_pos_direction(data) == keycode)
		view_pos_set(data, 0, 0);
	return (1);
}

void	redraw(t_cbdata *data)
{
	draw_map(data);
	draw_sprites(data);
}
