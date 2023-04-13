/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:11:31 by pjay              #+#    #+#             */
/*   Updated: 2023/04/13 11:10:37 by pjay             ###   ########.fr       */
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

unsigned int img_pix_read(t_img *img, double sreeen_y, bool north, t_point raycast)
{
	char *pixel;
	int		texture_x;
	int		texture_y;

	texture_y = sreeen_y * 64;
	//pixel = 0;
	if (north == true)
	{
		texture_x = fmod(raycast.y / (double)33, 1.0) * 64; // le 33 est egal a map->x a recup quelque part
	}
	else
	{
		texture_x = fmod(raycast.x / (double)33, 1.0) * 64;
	}
	pixel = ( img->addr + (texture_y * img->line_len + texture_x * (img->bpp / 8)));
	return (*(unsigned int *)pixel);
}

void	render_3d(t_cbdata *data)
{
 	int	i;
	unsigned int		color;
	int					column;
	//double	size_wall;
	double	size_to_print;
	int top_y;
	int bottom_y;
	int j;

	size_to_print = 0;
	i = 0;
	while (i < 1280)
	{
		//printf("angle = %f || M_PI/6.0 = %f\n", data->raycast[i].angle, M_PI /6.0);
		data->proj_slic_height[i] = BLOCK_SIZE / (data->raycast[i].dist * cos(data->angle - data->raycast[i].angle)) * PROJ_PLAN; // il faut que je recup l'angle par rapport a player dir pour reduire le fisheye
		//printf("data->proj_slic_height[%d] = %f || alldist  = %f\n", i, data->proj_slic_height[i],  data->all_dist[i]);
		i++;
	}
	i = 0;

		// size_wall = (tan(M_PI / 6.0) * (data->raycast[i].dist)) * 2.0;
		// size_wall = size_wall * cos(M_PI / 6);
	column = 0;
	while (column < PLANE_X)
	{
		size_to_print = data->proj_slic_height[column]; //PLANE_Y / size_wall * 64;
		//j = 0;
		top_y = (double)PLANE_Y / 2.0 - size_to_print / 2.0;
		bottom_y = (double)top_y + size_to_print;
		if (top_y < 0)
			top_y = 0;
		// if (bottom_y > PLANE_Y)
		// 	bottom_y = PLANE_Y;
		j = top_y;
		i = bottom_y;
		while (top_y <= bottom_y && top_y < PLANE_Y)
		{
			if (data->raycast[column].wall == 'N') // horizontal domc off set sur x
			{
				color = img_pix_read(&data->texture.wall_n, 1.0 - (double)(bottom_y - top_y) / size_to_print, false, data->raycast[column]);
			}
			else if (data->raycast[column].wall == 'S') // horizontal domc off set sur x
			{
				color = img_pix_read(&data->texture.wall_s, 1.0 - (double)(bottom_y - top_y) / size_to_print, false, data->raycast[column]);
			}
			else if (data->raycast[column].wall == 'E') // vertical domc off set sur y
			{
				color = img_pix_read(&data->texture.wall_e, 1.0 - (double)(bottom_y - top_y) / size_to_print, true, data->raycast[column]);
			}
			else // vertical domc off set sur y
			{
				color = img_pix_read(&data->texture.wall_w, 1.0 - (double)(bottom_y - top_y) / size_to_print, true, data->raycast[column]);
			}
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
			my_mlx_pixel_put(data, column, j, data->ceiling_color);
			j--;
		}
		column++;
		//printf("colums = %d\n", column);
	}

	// 	while (j < PLANE_Y)
	// 	{
	// 		if (j < 400 && PLANE_Y / 2.0 - size_to_print / 2.0 < j)
	// 		{
	// 			//printf("PLANE_Y / 2.0 - size_to_print / 2.0 = %f\n", size_to_print);
	// 			//Il faut ajouter i et/ou j pour read la texture
	// 			//printf("data->raycast[i].y = %f\n", fmod(data->raycast[i].y, 64));
	// 			if (data->raycast[i].wall == 'N') // horizontal domc off set sur x
	// 			{
	// 				double	offset = fmod(data->raycast[i].x, 64);
	// 				int		print = 0;
	// 				int		position = fmod(data->raycast[i].x / data->map_x, 1.0) * 64;
	// 				printf("ddd = %d|| data->map_x\n",  position);
	// 				color = img_pix_read(&data->texture.wall_n, offset, data->raycast[i].y);
	// 				print++;
	// 				if (print == 65)
	// 					print = 0;
	// 			}
	// 				 // si on est sur un mur vertical prendre modulo j sinon mudulo i
	// 			else if (data->raycast[i].wall == 'S')// horizontal domc off set sur x
	// 			{
	// 				double offset = fmod(data->raycast[i].x, 64);
	// 				int		print;
	// 				print = 0;
	// 				//printf("off set = %f\n", offset);
	// 				color = img_pix_read(&data->texture.wall_n, offset, data->raycast[i].y);
	// 				print++;
	// 				if (print == 65)
	// 					print = 0;
	// 			}
	// 			else if (data->raycast[i].wall == 'E') // vertical donc off set sur y
	// 			{
	// 				//printf("off set = %f\n", fmod(data->raycast[i].y, 64));
	// 				int		print;
	// 				print = 0;
	// 				color = img_pix_read(&data->texture.wall_s, data->raycast[i].x / 64, fmod(data->raycast[i].y, 64));
	// 				print++;
	// 				if (print == 65)
	// 					print = 0;
	// 			}
	// 			else if (data->raycast[i].wall == 'W') // vertical donc off set sur y
	// 			{
	// 				//ggprintf("off set = %f\n", fmod(data->raycast[i].y, 64));
	// 				int		print;
	// 				print = 0;
	// 				color = img_pix_read(&data->texture.wall_s, data->raycast[i].x / 64, fmod(data->raycast[i].y, 64));
	// 				print++;
	// 				if (print == 65)
	// 					print = 0;
	// 			}
	// 			else
	// 			 	color = 9198000;
	// 			if (!(i < 320 && j < 150)) // pas dessiner sur la minimap // censer etre 200 pour j mais minimap plus petitef (!(i < 320 && j < 200)) // pas dessiner sur la minimap
	// 				my_mlx_pixel_put(data, i, j, color);
	// 			//commencer a afficher le cube par le bas jusqu'au 400eme pixels
	// 		}
	// 		else if (j >= 400 && PLANE_Y / 2.0 + size_to_print / 2.0 > j)
	// 		{
	// 			//printf("data->raycast[i].y = %f || data->raycast[i].x = %f\n ", data->raycast[i].y, data->raycast[i].x );
	// 			if (data->raycast[i].wall == 'N') // horizontal domc off set sur x
	// 			{
	// 				double offset = fmod(data->raycast[i].x, 64);
	// 				int		print;
	// 				print = 0;
	// 				//printf("off set = %f\n", offset);
	// 				color = img_pix_read(&data->texture.wall_n, print, offset);
	// 				print++;
	// 				if (print == 65)
	// 					print = 0;
	// 			}
	// 				 // si on est sur un mur vertical prendre modulo j sinon mudulo i
	// 			else if (data->raycast[i].wall == 'S')// horizontal domc off set sur x
	// 			{
	// 				double offset = fmod(data->raycast[i].x, 64);
	// 				int		print;
	// 				print = 0;
	// 				//printf("off set = %f\n", offset);
	// 				color = img_pix_read(&data->texture.wall_n, print, offset);
	// 				print++;
	// 				if (print == 65)
	// 					print = 0;
	// 			}
	// 			else if (data->raycast[i].wall == 'E') // vertical donc off set sur y
	// 			{
	// 				//printf("off set = %f\n", fmod(data->raycast[i].y, 64));
	// 				color = img_pix_read(&data->texture.wall_s, data->raycast[i].x / 64, fmod(data->raycast[i].y, 64));
	// 			}
	// 			else if (data->raycast[i].wall == 'W') // vertical donc off set sur y
	// 			{
	// 				//ggprintf("off set = %f\n", fmod(data->raycast[i].y, 64));
	// 				color = img_pix_read(&data->texture.wall_s, data->raycast[i].x / 64, fmod(data->raycast[i].y, 64));
	// 			}
	// 			else
	// 			 	color = 9198000;
	// 			if (!(i < 320 && j < 150)) // pas dessiner sur la minimap // censer etre 200 pour j mais minimap plus petite
	// 				my_mlx_pixel_put(data, i, j,  color); // bordeau
	// 			// finir le cube a afficher
	// 		}
	// 		else
	// 		{
	// 			// affiche le sol ou le plafond
	// 			if (j < 400)
	// 			{
	// 				// plafond
	// 				//printf("PLANE_Y / 2.0 - size_to_print / 2 = %f || j = %d\n", PLANE_Y / 2.0 - size_to_print / 2, j);
	// 				if (!(i < 320 && j < 150)) // pas dessiner sur la minimap // censer etre 200 pour j mais minimap plus petiteif (!(i < 320 && j < 200)) // pas dessiner sur la minimap
	// 					my_mlx_pixel_put(data, i, j, data->ceiling_color);
	// 			}
	// 			else
	// 			{
	// 				if (!(i < 320 && j < 150)) // pas dessiner sur la minimap // censer etre 200 pour j mais minimap plus petiteif (!(i < 320 && j < 200)) // pas dessiner sur la minimap
	// 					my_mlx_pixel_put(data, i, j, data->floor_color);
	// 				//sol
	// 			}
	// 		}
	// 		j++;
	// 	}
	// 	//printf("size_wall * 2 = %f || size_to_print = %f\n", size_wall, size_to_print);
	// 	//printf("i = %d\n", i);
	// 	i++;
	}
	// to know wichh slice of the texture we need to draw
	// we determine the offset : if on a vertical grid (y % 64) else (x % 64)
	//data->angle_all = init_angle();

