/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:33:02 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/24 15:57:51 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static void init_cats(t_cbdata *data);


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
	init_cats(data);
}

void init_cats(t_cbdata *data)
{
	int		i;
	char	*str;
	char	*str2;
	char	*str3;

	(void)data;

	i = 0;
	while (i < 32)
	{
		str3 = ft_itoa(i);
		if (i < 10)
			str = ft_strjoin("./textures/petscuttedgood/0", str3);
		else
			str = ft_strjoin("./textures/petscuttedgood/", str3);
		str2 = ft_strjoin(str, "_petscuted.xpm");
		printf("%s\n", str2);
		data->texture.cats[i].mlx_img = mlx_xpm_file_to_image(data->mlx, \
				str2, &data->texture.cats[i].width, \
				&data->texture.cats[i].heigth);
		if (!data->texture.cats[i].mlx_img)
			cb_exit(data, "MLX_FAILED");
		data->texture.cats[i].addr = mlx_get_data_addr(
			data->texture.cats[i].mlx_img, &data->texture.cats[i].bpp, &data->texture.cats[i].line_len, \
			&data->texture.cats[i].endian);
		if (!data->texture.cats[i].addr)
			cb_exit(data, "MLX_FAILED");
		data->texture.cats[i].pos_x = 1696.0;
		data->texture.cats[i].pos_y = 394.0;
		free(str);
		free(str2);
		free(str3);
		i++;
	}
}
