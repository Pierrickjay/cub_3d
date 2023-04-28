/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image_bonus2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:42:45 by pjay              #+#    #+#             */
/*   Updated: 2023/04/28 09:43:26 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d_bonus.h"

void	load_win_img(t_cbdata *data)
{
	data->texture.youwin.mlx_img = mlx_xpm_file_to_image(data->mlx, \
			"./textures/youwin.xpm", &data->texture.youwin.width, \
			&data->texture.youwin.heigth);
	if (!data->texture.youwin.mlx_img)
		cb_exit(data, "MLX FAILED");
	data->texture.youwin.addr = mlx_get_data_addr(data->texture.youwin.mlx_img, \
		&data->texture.youwin.bpp, \
		&data->texture.youwin.line_len, &data->texture.youwin.endian);
	if (!data->texture.youwin.addr)
		cb_exit(data, "MLX FAILED");
}
