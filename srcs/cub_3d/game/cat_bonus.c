/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:25:32 by pjay              #+#    #+#             */
/*   Updated: 2023/04/25 16:38:04 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

void	draw_slice(t_cbdata *data, t_point screen, t_point cat, t_vec half_size, \
		int current_x, int offset_x, float reduct)
{
	int		offset_y;
	char	*cat_pixel;
	int		current_y;
	t_vec	pixel;
	(void)screen;
	(void)cat;
	offset_y = 0;
	pixel.x = SPRITE_L / 2  + offset_x / reduct;
	int ground = PLANE_Y / 2 + BLOCK_SIZE / 2 * reduct;
	//printf("offset_x %d, pixel.x %f\n", offset_x, pixel.x);
	while (offset_y <  half_size.y * 2)
	{
		current_y = ground - offset_y;
		if ( current_y >= 0 && current_y < PLANE_Y)
		{//DP
			//printf("current y: %d\n", current_y);
			pixel.y = SPRITE_H   - offset_y  / reduct;
			//printf("pixel.y %f\n", pixel.y);
		//	DP
				int pixx = (int)pixel.x;
				int pixy = (int)pixel.y;
				//printf("x is %d and y is %d\n", pixx, pixy);
			cat_pixel = data->texture.cat[0].addr + pixy * data->texture.cat[0].line_len  \
					+ pixx * data->texture.cat[0].bpp / 8;
			//DP
			if ((*(unsigned int *)cat_pixel & 0x00FFFFF) != 0)
				my_mlx_pixel_put(data, current_x, current_y,*(unsigned int *)cat_pixel);//0xFF5733 
		//	DP
		}
		offset_y++;
	}
}

void	put_cat(t_cbdata *data)
{
	float	reduct;
	int		offset;
	t_vec	half_size;
	int		current;
	t_point	cat;
	t_point	screen;

	cat.x = data->cats[0].pos.x - data->pos_x;
	cat.y = data->cats[0].pos.y - data->pos_y;
	cat.angle = atanf(- cat.y / cat.x);
	cat.dist = sqrt(cat.x * cat.x + cat.y *cat.y);

printf("cat x: %f, y: %f, angle %f, dist %f\n", cat.x, cat.y, cat.angle, cat.dist);

	screen.angle = data->angle - cat.angle;
	screen.x = PROJ_PLAN * tanf(screen.angle);
	
printf("screen x: %f, angle %f\n", screen.x, screen.angle);
	reduct = cosf(screen.angle) * PROJ_PLAN / cat.dist;
printf("reduct : %f\n", reduct);
	half_size.x = SPRITE_L * reduct / 2;
	half_size.y = SPRITE_H * reduct / 2;
printf("half size: x %f, y %f\n", half_size.x, half_size.y);
	offset  =  - half_size.x;
	while (offset <=  (int)half_size.x)
	{
		current = PLANE_X / 2 + (int)screen.x + offset;
		if (current >= 0 && current < PLANE_X)
		{
			draw_slice(data, screen, cat, half_size, current, offset, reduct);
		}
		offset++;
	}
}
