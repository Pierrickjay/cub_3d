/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:54:56 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/26 16:21:39 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

static void	put_slice(t_cbdata *data, t_vec pixel, int cur_x, int cur_y);

void	draw_slice(t_cbdata *data, int current_x, t_app_cat kitty)
{
	int		current_y;
	int		ground;
	t_vec	pixel;
	pixel.x = kitty.offset_x / kitty.reduct;
	ground = PLANE_Y / 2 + BLOCK_SIZE / 2 * kitty.reduct;
	while (kitty.offset_y < kitty.y)
	{
		current_y = ground - kitty.offset_y;
		if (current_y >= 0 && current_y < PLANE_Y)
		{
			pixel.y = SPRITE_H - kitty.offset_y / kitty.reduct;
			put_slice(data, pixel, current_x, current_y);
		}
		kitty.offset_y++;
	}
}

static void	put_slice(t_cbdata *data, t_vec pixel, int cur_x, int cur_y)
{
	char	*cat_pixel;

	cat_pixel = data->texture.cat[0].addr + (int)pixel.y \
				* data->texture.cat[0].line_len \
				+ (int)pixel.x * data->texture.cat[0].bpp / 8;
	if ((*(unsigned int *)cat_pixel & 0x00FFFFF) != 0)
		my_mlx_pixel_put(data, cur_x, cur_y, \
				*(unsigned int *)cat_pixel);
}
