/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:06:01 by pjay              #+#    #+#             */
/*   Updated: 2023/04/27 10:45:07 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d_bonus.h"

static void	load_wall(t_cbdata *data, int i);
static void	load_cats(t_cbdata *data, int i);
static int	cats_mlx(t_cbdata *data, int i, char *str2);

void	load_img_bonus(t_cbdata *data)
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

static int	cats_mlx(t_cbdata *data, int i, char *str2)
{
	data->texture.cat[i].mlx_img = mlx_xpm_file_to_image(data->mlx, \
			str2, &data->texture.cat[i].width, \
			&data->texture.cat[i].heigth);
	if (!data->texture.cat[i].mlx_img)
		return (-1);
	data->texture.cat[i].addr = mlx_get_data_addr(
			data->texture.cat[i].mlx_img, &data->texture.cat[i].bpp, \
			&data->texture.cat[i].line_len, &data->texture.cat[i].endian);
	if (!data->texture.cat[i].addr)
		return (-1);
	return (0);
}

static void	load_cats(t_cbdata *data, int i)
{
	char	*str;
	char	*str2;
	char	*str3;

	str3 = ft_itoa(i);
	str2 = NULL;
	str = NULL;
	if (!str3)
		cb_exit(data, "MALLOC FAILED");
	if (i < 10)
		str = ft_strjoin("./textures/petscutted2/0", str3);
	else
		str = ft_strjoin("./textures/petscutted2/", str3);
	if (!str)
		ft_tripple_free_malloc(str, str2, str3, data);
	str2 = ft_strjoin(str, "_petscuted.xpm");
	if (!str2)
		ft_tripple_free_malloc(str, str2, str3, data);
	if (cats_mlx(data, i, str2) == -1)
		ft_tripple_free_mlx(str, str2, str3, data);
	free(str);
	free(str2);
	free(str3);
}
