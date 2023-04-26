/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:54:56 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/26 18:52:16 by pjay             ###   ########.fr       */
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

long long int	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static void	put_slice(t_cbdata *data, t_vec pixel, int cur_x, int cur_y)
{
	char					*cat_pixel;
	long long int			time;
	static int				i = 0;
	static long long int	old_time = 0;

	time = current_time();
	if (time - old_time > 200 || old_time == 0)
	{
		i++;
		old_time = time;
	}
	cat_pixel = data->texture.cat[i].addr + (int)pixel.y \
				* data->texture.cat[i].line_len \
				+ (int)pixel.x * data->texture.cat[i].bpp / 8;
	if ((*(unsigned int *)cat_pixel & 0x00FFFFF) != 0)
		my_mlx_pixel_put(data, cur_x, cur_y, \
				*(unsigned int *)cat_pixel);
	if (i == 7)
		i = 0;
}
