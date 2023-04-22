/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:55:31 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/22 11:47:08 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

int	get_color(t_img *img, int x, int y)
{
	int	color;

	color = *(int *)(img->addr
			+ (4 * (int)img->width * ((int)img->heigth - 1 - y))
			+ (4 * x));
	return (color & 0xFFFFFF);
}

unsigned int	img_pix_read(t_cbdata *data, int text_y, int column)
{
	char	*pixel;
	int		text_x;
	int		wall;
	t_img	*img;

	wall = data->raycast[column].wall;
	img = &data->texture.wall[wall];
	if (data->raycast[column].wall == e || data->raycast[column].wall == w)
		text_x = (int)data->raycast[column].y % BLOCK_SIZE;
	else
		text_x = (int)data->raycast[column].x % BLOCK_SIZE;
	pixel = (img->addr + text_y * img->line_len + text_x * img->bpp / 8);
	return (*(unsigned int *)pixel);
}
