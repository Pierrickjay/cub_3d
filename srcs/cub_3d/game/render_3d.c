/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:11:31 by pjay              #+#    #+#             */
/*   Updated: 2023/04/11 14:09:08 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

t_angle	init_angle(void )
{
	t_angle angle;

	angle.ANGLE60 = MINI_Y;
	angle.ANGLE30 = angle.ANGLE60 / 2;
	angle.ANGLE15 = angle.ANGLE30 / 2;
	angle.ANGLE90 = angle.ANGLE30 * 3;
	angle.ANGLE180 = angle.ANGLE90 * 2;
	angle.ANGLE270 = angle.ANGLE90 * 3;
	angle.ANGLE360 = angle.ANGLE60 * 6;
	angle.ANGLE0 = 0;
	angle.ANGLE5 = angle.ANGLE30 / 6;
	angle.ANGLE10 = angle.ANGLE5 * 2;
	angle.ANGLE45 = angle.ANGLE15 * 3;
	return (angle);
}

int	get_color(t_img *img, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int *)(img->addr
			+ (4 * (int)img->width * ((int)img->heigth - 1 - y))
			+ (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

unsigned int img_pix_read(t_img *img, int x, int y)
{
	char *pixel;

	//pixel = 0;

	pixel = ( img->addr + (y * img->line_len + x * (img->bpp / 8)));
	return (*(unsigned int *)pixel);
}

void	render_3d(t_cbdata *data)
{
 	int	i;
	unsigned int		color;
	double	size_wall;
	double	size_to_print;

	i = 0;
	while (i < 1280)
	{
		data->proj_slic_height[i] = BLOCK_SIZE * 4 / data->all_dist[i] * PROJ_PLAN;
		//printf("data->proj_slic_height[%d] = %f || alldist  = %f\n", i, data->proj_slic_height[i],  data->all_dist[i]);
		i++;
	}
	i = 0;
	while (i < PLANE_X)
	{
		size_wall = (tan(M_PI / 6.0) * data->all_dist[i]) * 2.0;
		size_to_print = PLANE_Y / size_wall * 256;
		int j = 0;
		while (j < PLANE_Y)
		{
			if (j <= 400 && (int)PLANE_Y / 2.0 - (int)size_to_print / 2 <= j)
			{
				color = img_pix_read(&data->wall, i % 256, j % 256);// si on est sur un mur vertical prendre modulo j sinon mudulo i
				my_mlx_pixel_put(data, i, j,color);
				//commencer a afficher le cube par le bas jusqu'au 400eme pixels
			}
			else if (j >= 400 && (int)PLANE_Y / 2.0 + (int)size_to_print / 2 >= j)
			{
				color = img_pix_read(&data->wall, i % 256, j % 256); // si on est sur un mur vertical prendre modulo j sinon mudulo i
				my_mlx_pixel_put(data, i, j, color); // bordeau
				// finir le cube a afficher
			}
			else
			{
				// affiche le sol ou le plafond
				if (j < 400)
				{
					// plafond
					//printf("PLANE_Y / 2.0 - size_to_print / 2 = %f || j = %d\n", PLANE_Y / 2.0 - size_to_print / 2, j);
					my_mlx_pixel_put(data, i, j, 5262875);
				}
				else
				{
					my_mlx_pixel_put(data, i, j, 5262974);
					//sol
				}
			}
			j++;
		}
		//printf("size_wall * 2 = %f || size_to_print = %f\n", size_wall, size_to_print);
		i++;
	}
	// to know wichh slice of the texture we need to draw
	// we determine the offset : if on a vertical grid (y % 64) else (x % 64)
	//data->angle_all = init_angle();
}
