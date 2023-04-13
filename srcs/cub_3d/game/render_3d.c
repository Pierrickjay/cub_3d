/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:11:31 by pjay              #+#    #+#             */
/*   Updated: 2023/04/13 11:57:19 by pjay             ###   ########.fr       */
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

unsigned int img_pix_read(t_img *img, double sreeen_y, t_cbdata *data, int column)
{
	char *pixel;
	int		texture_x;
	int		texture_y;

	texture_y = sreeen_y * 64;
	//pixel = 0;
	if (data->raycast[column].wall == 'E' || data->raycast[column].wall == 'W')
	{
		texture_x = fmod(data->raycast[column].y / (double)data->map_x, 1.0) * BLOCK_SIZE;
	}
	else
	{
		texture_x =fmod(data->raycast[column].x / (double)data->map_x, 1.0) * BLOCK_SIZE;
	}
	pixel = ( img->addr + (texture_y * img->line_len + texture_x * (img->bpp / 8)));
	return (*(unsigned int *)pixel);
}

void	render_3d(t_cbdata *data)
{
 	int				i;
	unsigned int	color;
	int				column;
	double			size_to_print;
	int				top_y;
	int				bottom_y;
	int				j;

	size_to_print = 0;
	i = 0;
	while (i < 1280)
	{
		//printf("angle = %f || M_PI/6.0 = %f\n", data->raycast[i].angle, M_PI /6.0);
		data->proj_slic_height[i] = (double)BLOCK_SIZE / (data->raycast[i].dist * cos(data->angle - data->raycast[i].angle)) * PROJ_PLAN; // il faut que je recup l'angle par rapport a player dir pour reduire le fisheye
		//printf("data->proj_slic_height[%d] = %f || alldist  = %f\n", i, data->proj_slic_height[i],  data->all_dist[i]);
		i++;
	}
	i = 0;
	column = 0;
	while (column < PLANE_X) // regarder si je dessine pas dans le mauvais sens.
	{
		size_to_print = data->proj_slic_height[column]; //PLANE_Y / size_wall * 64;
		//j = 0;
		top_y = (double)PLANE_Y / 2.0 - size_to_print / 2.0;
		bottom_y = (double)top_y + size_to_print;
		if (top_y < 0)
			top_y = 0;
		j = top_y;
		i = bottom_y;
		while (top_y <= bottom_y && top_y < PLANE_Y)
		{
			if (data->raycast[column].wall == 'N') // horizontal domc off set sur x
			{
				color = img_pix_read(&data->texture.wall_n, 1.0 - (double)(bottom_y - top_y) / size_to_print, data, column);
			}
			else if (data->raycast[column].wall == 'S') // horizontal domc off set sur x
			{
				color = img_pix_read(&data->texture.wall_s, 1.0 - (double)(bottom_y - top_y) / size_to_print, data, column);
			}
			else if (data->raycast[column].wall == 'E') // vertical domc off set sur y
			{
				color = img_pix_read(&data->texture.wall_e, 1.0 - (double)(bottom_y - top_y) / size_to_print, data, column);
			}
			else // vertical domc off set sur y
			{
				color = img_pix_read(&data->texture.wall_w, 1.0 - (double)(bottom_y - top_y) / size_to_print, data, column);
			}
			if (!(column < 320 && top_y < 150))
				my_mlx_pixel_put(data, column, top_y, color);
			top_y++;
			//printf("top_y = %d || column= %d\n", top_y, column);
		}
		while (i < 800)
		{
			// pas dessiner sur la minimap // censer etre 200 pour j mais minimap plus petiteif (!(i < 320 && j < 200)) // pas dessiner sur la minimap
			my_mlx_pixel_put(data, column, i, data->floor_color);
			i++; // sol
		}
		while (j > 0)
		{
			if (!(column < 320 && j < 150))
				my_mlx_pixel_put(data, column, j, data->ceiling_color);
			j--;
		}
		column++;
	}
}
	// to know wichh slice of the texture we need to draw
	// we determine the offset : if on a vertical grid (y % 64) else (x % 64)
	//data->angle_all = init_angle();

