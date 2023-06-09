/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:33:02 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/27 10:43:33 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static void	load_wall(t_cbdata *data, int i);

void	load_img(t_cbdata *data)
{
	int	i;

	if (!data->mlx)
	{
		cb_exit(data, "MLX FAILED");
		exit(1);
	}
	i = -1;
	while (++i < 4)
		load_wall(data, i);
}

static void	load_wall(t_cbdata *data, int i)
{
	data->texture.wall[i].mlx_img = mlx_xpm_file_to_image(data->mlx, \
			data->texture_file[i], &data->texture.wall[i].width, \
			&data->texture.wall[i].heigth);
	if (!data->texture.wall[i].mlx_img)
		cb_exit(data, "MLX FAILED");
	data->texture.wall[i].addr = \
		mlx_get_data_addr(data->texture.wall[i].mlx_img, \
		&data->texture.wall[i].bpp, \
		&data->texture.wall[i].line_len, &data->texture.wall[i].endian);
	if (!data->texture.wall[i].addr)
		cb_exit(data, "MLX FAILED");
}
