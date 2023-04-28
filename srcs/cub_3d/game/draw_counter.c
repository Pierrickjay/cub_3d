/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:45:58 by pjay              #+#    #+#             */
/*   Updated: 2023/04/28 10:17:25 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d_bonus.h"

static void	draw_counter_2(t_cbdata *data);

void	draw_win(t_cbdata *data)
{
	int		x;
	int		y;
	char	*pixel;
	t_img	*img;

	img = &data->texture.youwin;
	x = 0;
	while (x < img->width)
	{
		y = 0;
		while (y < img->heigth)
		{
			pixel = (img->addr + y * img->line_len + x * img->bpp / 8);
			if ((*(unsigned int *)pixel & 0x00FFFFF) != 0)
				my_mlx_pixel_put(data, PLANE_X - 1000 + x, \
					50 + y, *(unsigned int *)pixel);
			y++;
		}
		x++;
	}
}

void	draw_counter_seen(t_cbdata *data)
{
	char		*counter;
	size_t		digits;
	size_t		i;

	counter = ft_itoa(data->nb_cats_see);
	digits = ft_strlen(counter);
	i = -1;
	data->digits = digits;
	while (++i < digits)
	{
		if (PLANE_X < digits + i)
			break ;
		mlx_put_image_to_window(data->mlx, data->mlx_win, \
				data->texture.number[counter[i] - '0'].mlx_img, \
				PLANE_X - (64 * (digits - i)), 0);
	}
	free(counter);
	draw_counter_2(data);
}

static void	draw_counter_2(t_cbdata *data)
{
	char	*counter;
	size_t	digits;
	size_t	i;

	counter = ft_itoa(data->nb_cats);
	digits = ft_strlen(counter);
	i = -1;
	data->digits_all = digits;
	while (++i < digits)
	{
		if (PLANE_X < digits + i)
			break ;
		mlx_put_image_to_window(data->mlx, data->mlx_win, \
				data->texture.number[counter[i] - '0'].mlx_img, \
				PLANE_X - (64 * (digits - i)), 64);
	}
	free(counter);
}
