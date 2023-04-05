/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:18:23 by pjay              #+#    #+#             */
/*   Updated: 2023/04/05 13:40:51 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	set_moove_player(t_cbdata *data, int keycode)
{
	// static int	i = 0;
	static int	mvcount = 0;

	(void)data;
	// if (i == 4)
	// 		i = 0;
	if (keycode == 119 || keycode == 65362)
		mvcount++;
	if (keycode == 115 || keycode == 65364)
		mvcount++;
	if (keycode == 97 || keycode == 65361)
		mvcount++;
	if (keycode == 100 || keycode == 65363)
		mvcount++;
	printf("Nombre de deplacement = %d\n", mvcount);
}

int	key_press_hook(int keycode, t_cbdata *data)
{
	if (keycode == XK_Escape)
		cb_exit(data, NULL);
	if (keycode == 119 || keycode == 65362 || keycode == 115 || keycode == 65364
		|| keycode == 97 || keycode == 65361 || keycode == 100
		|| keycode == 65363)
		set_moove_player(data, keycode);
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
