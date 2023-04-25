/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 10:57:33 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/25 14:24:18 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#define UDIV 1
#define VDIV 1
#define VMOVE 400.0
static void	set_slice_height(t_cbdata *data);
static void	set_column(t_cbdata *data, t_column *col);

t_vec	angle_to_vec(t_cbdata *data)
{
	t_vec vec;

	vec.dir_x = cos(data->angle);
	vec.dir_y = -sin(data->angle);
	return (vec);
}

void	draw_cats_center(t_cbdata *data)
{
	float	sprite_x;
	float	sprite_y;
	float	sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	float	sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		sprite_screen_x;
	float	inv_mat;
	float	transform_x;
	float	transform_y;
	int		x;
	int		y;
	int		tex_x;
	int		tex_y;
	char	*pixel;
	int		v_move_screen;
	//static	int	v_div = 9;

	sprite_x = data->texture.cats[0].pos_x - data->pos_x; // sprite position relative to camera
	sprite_y = data->texture.cats[0].pos_y - data->pos_y/* + (200 % (int)data->pos_y)*/;
	printf("sprite_x = %f || sprite_y = %f\n", sprite_x, sprite_y);
	// if (sprite_y < 0)
	// 	sprite_y *= -1;

	if (sprite_x == 0 && sprite_y == 0)
		return ;
	data->texture.cats[0].vec = angle_to_vec(data);
	inv_mat = 1.0 / (PLANE_X * data->texture.cats[0].vec.dir_y - data->texture.cats[0].vec.dir_x * PLANE_Y);
	transform_x = inv_mat * (data->texture.cats[0].vec.dir_y * sprite_x - data->texture.cats[0].vec.dir_x * sprite_y);
	transform_y = inv_mat * (-PLANE_Y * sprite_x + PLANE_X * sprite_y); // permet de passe dun plan en negatif en pos et inversement
	//int vMoveScreen = (int)(VMOVE / transform_y);
	v_move_screen  = (int)(VMOVE / transform_y) ;
	sprite_screen_x = (int)((PLANE_X / 2) * (1 + transform_x / transform_y));
	sprite_height = abs((int)(PLANE_Y / transform_y) * 20); /// 1.0;
	printf("v_move_screen= %d || transform y = %f\n", v_move_screen, transform_y);
	//v_div -= 0.05;
	//printf("sprite_x = %f || sprite_y= %f || sprite height = %f\n", sprite_x, sprite_y, sprite_height)
	draw_start_y = -sprite_height / 2 + PLANE_Y / 2 + v_move_screen;//+ v_move_screen;
	//printf("sprite_height = %f || tranform y = %f || sprite_screen_x = %d|| transform_x = %f\n",sprite_height, transform_y,sprite_screen_x, transform_x);
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_height / 2 + PLANE_Y / 2 + v_move_screen;//+ v_move_screen;
	if (draw_end_y >= PLANE_Y)
		draw_end_y = PLANE_Y - 1;
	//printf("draw_end_y = %f || draw start =%f || draw_end_y = %f || draw start =%f\n", sprite_height / 2 + PLANE_Y / 2, -sprite_height / 2 + PLANE_Y / 2, draw_end_y, draw_start_y);
	sprite_width = sprite_height;
	draw_start_x = sprite_width * -1 / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_width / 2 + sprite_screen_x;
	//printf("draw_end x = %d\n", draw_end_x);
	if (draw_end_x >= PLANE_X)
		draw_end_x = PLANE_X - 1;
	x = draw_start_x;
	//printf("draw_start_x = %d || draw_end_x = %d || draw_start_y = %d || draw_end_y = %d\n",draw_start_x,draw_end_x,draw_start_y, draw_end_y);
	while (x < draw_end_x)
	{
		tex_x = (int)((256 * (x - (SPRITE_L * -1 / 2 + sprite_screen_x)) * BLOCK_SIZE / SPRITE_L) / 256) % SPRITE_L;
		y = draw_start_y;
		//printf("draw_start_y = %d || transform_y = %d\n",transform_y, draw_start_y, draw_end_y);
		//printf("tex_x = %d\n", tex_x);
		if (transform_y > 0 && x > 0 && x < PLANE_X /*&& transform_y <*/ )
		{
			while (y < draw_end_y)
			{
				//DP
				int d = (y -  v_move_screen) * 256 - PLANE_Y * 128 + sprite_height * 128; //- v_move_screen 256 && 128 pour empecher d'avoir trop de virgule
				tex_y = ((d * BLOCK_SIZE) / sprite_height) / 256;
				//tex_y =
				//printf("tex x = %d || tex_y = %d\n", tex_x, tex_y);
				if (tex_x < 0 || tex_y < 0)
					break;
				pixel = (data->texture.cats[0].addr + (tex_y * data->texture.cats[0].line_len + tex_x * (data->texture.cats[0].bpp / 8)));
				//fmod(data->raycast[column].y / (float)data->map_x, 1.0) * BLOCK_SIZE
				if ((*(unsigned int *)pixel & 0x00FFFFFF) != 0)
				{
					printf("y + (data->proj_slice_height[y] / 2) = %f\n", y + (data->proj_slice_height[y] / 2));
					my_mlx_pixel_put(data, x, (int)y + (data->proj_slice_height[y] / 3) , *(unsigned int *)pixel);
				}
				y++;
			}
		}
		x++;
	}
}
void	render_3d(t_cbdata *data)
{
	int				i;
	t_column		col;
	unsigned int	color;

	set_slice_height(data);
	col.column = -1;
	while (++col.column < PLANE_X)
	{
		set_column(data, &col);
		i = -1;
		while (++i < PLANE_Y)
		{
			if (col.column < MINI_X && i < MINI_Y)
				continue ;
			else if (i < col.top)
				color = data->cf_color[1];
			else if (i <= col.bottom)
				color = img_pix_read(data, (BLOCK_SIZE * (i - col.top)) \
						/ col.size, col.column);
			else
				color = data->cf_color[0];
			my_mlx_pixel_put(data, col.column, i, color);
		}
	}
	draw_cats_center(data);

}

static void	set_column(t_cbdata *data, t_column *col)
{
	col->size = (int)data->proj_slice_height[col->column];
	col->top = (PLANE_Y - col->size) / 2;
	col->bottom = col->top + col->size;
}

static void	set_slice_height(t_cbdata *data)
{
	int	i;

	i = -1;
	while (++i < 1280)
		data->proj_slice_height[i] = (float)BLOCK_SIZE * PROJ_PLAN \
				/ (data->raycast[i].dist \
				* cos(data->angle - data->raycast[i].angle));
}
