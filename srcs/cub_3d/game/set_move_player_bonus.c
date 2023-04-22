/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_move_player_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:54:25 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/22 13:59:27 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static int	get_keyboard_plus_entry(int keycode);
static int	get_keyboard_minus_entry(int keycode);

void	set_move_player(t_cbdata *data, int keycode, int value)
{
	int	key;

	key = get_keyboard_plus_entry(keycode);
	if (key > -1)
	{
		data->keypressed[key] = value;
		return ;
	}
	key = get_keyboard_minus_entry(keycode);
	if (key > -1)
	{
		data->keypressed[key] = -1 * value;
		return ;
	}
}

static int	get_keyboard_plus_entry(int keycode)
{
	int	i;
	int	keyboard_plus[6];

	keyboard_plus[down] = KEY_S;
	keyboard_plus[right] = KEY_D;
	keyboard_plus[little_right_view] = LITTLE_RIGHT;
	keyboard_plus[half_right_view] = HALF_RIGHT;
	keyboard_plus[mouse_right] = MOUSE_RIGHT;
	keyboard_plus[right_view] = KEY_RIGHT;
	i = -1;
	while (++i < 6)
	{
		if (keyboard_plus[i] == keycode)
			return (i);
	}
	return (-1);
}

static int	get_keyboard_minus_entry(int keycode)
{
	int	i;
	int	keyboard_minus[6];

	keyboard_minus[down] = KEY_W;
	keyboard_minus[right] = KEY_A;
	keyboard_minus[little_right_view] = LITTLE_LEFT;
	keyboard_minus[half_right_view] = HALF_LEFT;
	keyboard_minus[mouse_right] = MOUSE_LEFT;
	keyboard_minus[right_view] = KEY_LEFT;
	i = -1;
	while (++i < 6)
	{
		if (keyboard_minus[i] == keycode)
			return (i);
	}
	return (-1);
}
