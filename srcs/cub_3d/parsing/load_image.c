/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:33:02 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/27 09:57:01 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static void	load_wall(t_cbdata *data, int i);
static void	load_cats(t_cbdata *data, int i);

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
	i = -1;
	while (++i < 8)
		load_cats(data, i);
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

static void	load_cats(t_cbdata *data, int i)
{
	char	*str;
	char	*str2;
	char	*str3;

	str3 = ft_itoa(i);
	if (i < 10)
		str = ft_strjoin("./textures/petscutted2/0", str3);
	else
		str = ft_strjoin("./textures/petscuttedgood/", str3);
	str2 = ft_strjoin(str, "_petscuted.xpm");
	data->texture.cat[i].mlx_img = mlx_xpm_file_to_image(data->mlx, \
			str2, &data->texture.cat[i].width, \
			&data->texture.cat[i].heigth);
	if (!data->texture.cat[i].mlx_img)
		cb_exit(data, "MLX_FAILED");
	data->texture.cat[i].addr = mlx_get_data_addr(
			data->texture.cat[i].mlx_img, &data->texture.cat[i].bpp, \
			&data->texture.cat[i].line_len, &data->texture.cat[i].endian);
	if (!data->texture.cat[i].addr)
		cb_exit(data, "MLX_FAILED");
	free(str);
	free(str2);
	free(str3);
}
