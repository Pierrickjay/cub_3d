/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:11:31 by pjay              #+#    #+#             */
/*   Updated: 2023/04/11 16:55:48 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

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
	//unsigned int		color;
	double	size_wall;
	double	size_to_print;

	i = 0;
	while (i < 1280)
	{
		data->proj_slic_height[i] = BLOCK_SIZE * 4 / (data->raycast[i].dist * cos(M_PI / 6)) * PROJ_PLAN;
		//printf("data->proj_slic_height[%d] = %f || alldist  = %f\n", i, data->proj_slic_height[i],  data->all_dist[i]);
		i++;
	}
	i = 0;
	while (i < PLANE_X)
	{
		size_wall = (tan(M_PI / 6.0) * (data->raycast[i].dist * cos(M_PI / 6))) * 2.0;
		size_to_print = PLANE_Y / size_wall * 256;
		int j = 0;
		while (j < PLANE_Y)
		{
			if (j <= 400 && (int)PLANE_Y / 2.0 - (int)size_to_print / 2 <= j)
			{
				// if (data->raycast[i].wall == 'N')
				// 	color = img_pix_read(&data->texture.wall_n,data->raycast[i].x ,data->raycast[i].y); // si on est sur un mur vertical prendre modulo j sinon mudulo i
				// else if (data->raycast[i].wall == 'S')
				// 	color = img_pix_read(&data->texture.wall_s,data->raycast[i].x ,data->raycast[i].y);
				// else if (data->raycast[i].wall == 'E')
				// 	color = img_pix_read(&data->texture.wall_e,data->raycast[i].x ,data->raycast[i].y);
				// else
				// 	color = img_pix_read(&data->texture.wall_w,data->raycast[i].x ,data->raycast[i].y);
				my_mlx_pixel_put(data, i, j, 9797962/*color*/);
				//commencer a afficher le cube par le bas jusqu'au 400eme pixels
			}
			else if (j >= 400 && (int)PLANE_Y / 2.0 + (int)size_to_print / 2 >= j)
			{
				// if (data->raycast[i].wall == 'N')
				// 	color = img_pix_read(&data->texture.wall_n,data->raycast[i].x ,data->raycast[i].y); // si on est sur un mur vertical prendre modulo j sinon mudulo i
				// else if (data->raycast[i].wall == 'S')
				// 	color = img_pix_read(&data->texture.wall_s,data->raycast[i].x ,data->raycast[i].y);
				// else if (data->raycast[i].wall == 'E')
				// 	color = img_pix_read(&data->texture.wall_e,data->raycast[i].x ,data->raycast[i].y);
				// else
				// 	color = img_pix_read(&data->texture.wall_w,data->raycast[i].x ,data->raycast[i].y);
				my_mlx_pixel_put(data, i, j,  9797962/*color*/); // bordeau
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
