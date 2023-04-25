/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:25:32 by pjay              #+#    #+#             */
/*   Updated: 2023/04/25 17:07:39 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#define UDIV 1
#define VDIV 1
#define VMOVE 0.0

// t_vec	angle_to_vec(t_cbdata *data)
// {
// 	t_vec vec;

// 	vec.x = cos(data->angle);
// 	vec.y = -sin(data->angle);
// 	return (vec);
// }

// void	draw_cats_center(t_cbdata *data)
// {
// 	t_vec	sprite;
// 	float	sprite_height;
// 	int		draw_start_y;
// 	int		draw_end_y;
// 	float	sprite_width;
// 	int		draw_start_x;
// 	int		draw_end_x;
// 	int		sprite_screen_x;
// 	float	inv_mat;
// 	float	transform_x;
// 	float	transform_y;
// 	int		x;
// 	int		y;
// 	int		tex_x;
// 	int		tex_y;
// 	char	*pixel;
// 	int		v_move_screen;

// 	sprite.x = data->cats->pos.x - data->pos_x;
// 	sprite.y = data->cats->pos.y - data->pos_y;
// printf("sprite x: %f, y: %f\n", sprite.x, sprite.y);
// 	if (sprite.x == 0 && sprite.y == 0)
// 		return ;
// 	data->cats->dir = angle_to_vec(data);
// 	inv_mat = 1.0 / (PLANE_X * data->cats->dir.y - data->cats->dir.x * PLANE_Y);
// 	transform_x = inv_mat * (data->cats->dir.y * sprite.x - data->cats->dir.x * sprite.y);
// 	transform_y = inv_mat * (-PLANE_Y * sprite.x + PLANE_X * sprite.y);
// 	v_move_screen = (int)(VMOVE / transform_y) ;
// 	sprite_screen_x = (int)((PLANE_X / 2) * (1 + transform_x / transform_y));
// 	sprite_height = abs((int)(PLANE_Y / transform_y)); /// 1.0;
// 	//printf("sprite_x = %f || sprite_y= %f || sprite height = %f\n", sprite.x, sprite.y, sprite_height)
// 	draw_start_y = -sprite_height / 2 + PLANE_Y / 2 ;//+ v_move_screen;
// 	//printf("sprite_height = %f || tranform y = %f || sprite_screen_x = %d|| transform_x = %f\n",sprite_height, transform_y,sprite_screen_x, transform_x);
// 	if (draw_start_y < 0)
// 		draw_start_y = 0;
// 	draw_end_y = sprite_height / 2 + PLANE_Y / 2 ;//+ v_move_screen;
// 	if (draw_end_y >= PLANE_Y)
// 		draw_end_y = PLANE_Y - 1;
// 	//printf("draw_end_y = %f || draw start =%f || draw_end_y = %f || draw start =%f\n", sprite_height / 2 + PLANE_Y / 2, -sprite_height / 2 + PLANE_Y / 2, draw_end_y, draw_start_y);
// 	sprite_width = sprite_height;
// 	draw_start_x = sprite_width * -1 / 2 + sprite_screen_x;
// 	if (draw_start_x < 0)
// 		draw_start_x = 0;
// 	draw_end_x = sprite_width / 2 + sprite_screen_x;
// 	//printf("draw_end x = %d\n", draw_end_x);
// 	if (draw_end_x >= PLANE_X)
// 		draw_end_x = PLANE_X - 1;
// 	x = draw_start_x;
// 	//printf("draw_start_x = %d || draw_end_x = %d || draw_start_y = %d || draw_end_y = %d\n",draw_start_x,draw_end_x,draw_start_y, draw_end_y);
// 	while (x < draw_end_x)
// 	{
// 		tex_x = (int)(256 * (x - (SPRITE_L * -1 / 2 + sprite_screen_x)) * BLOCK_SIZE / SPRITE_L) / 256;
// 		y = draw_start_y;
// 		//printf("draw_start_y = %d || transform_y = %d\n",transform_y, draw_start_y, draw_end_y);
// 		//printf("tex_x = %d\n", tex_x);
// 		if (transform_y > 0 && x > 0 && x < PLANE_X /*&& transform_y <*/ )
// 		{
// 			while (y < draw_end_y)
// 			{
// 				//DP
// 				int d = (y ) * 256 - PLANE_Y * 128 + sprite_height * 128; //- v_move_screen 256 && 128 pour empecher d'avoir trop de virgule
// 				tex_y = ((d * BLOCK_SIZE) / sprite_height) / 256;
// 				//tex_y =
// 				//printf("tex x = %d || tex_y = %d\n", tex_x, tex_y);
// 				if (tex_x < 0 || tex_y < 0)
// 					break ;
// 				pixel = (data->texture.cat[0].addr + (tex_y * data->texture.cat[0].line_len + tex_x * (data->texture.cat[0].bpp / 8)));
// 				//fmod(data->raycast[column].y / (float)data->map_x, 1.0) * BLOCK_SIZE
// 				if ((*(unsigned int *)pixel & 0x00FFFFFF) != 0)
// 					my_mlx_pixel_put(data, x, y, *(unsigned int *)pixel);
// 				y++;
// 			}
// 		}
// 		x++;
// 	}
// }
