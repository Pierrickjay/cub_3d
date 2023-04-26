/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:25:32 by pjay              #+#    #+#             */
/*   Updated: 2023/04/26 13:27:16 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

static t_point	set_cat(t_cbdata *data, int n);
static t_point	set_screen(t_cbdata *data, t_point cat);
static t_app_cat	set_app_cat(float angle, float dist);

void	put_cat(t_cbdata *data)
{
	t_app_cat	kitty;
	int		current;
	float	left;
	t_point	cat;
	t_point	screen;


	cat = set_cat(data, 0);
	screen = set_screen(data, cat);

	if (screen.angle > M_PI_2 && screen.angle < 3 * M_PI_2)
		return ;
	kitty = set_app_cat(screen.angle, cat.dist);
	left = screen.x - kitty.x / 2.0; 
	while (kitty.offset_x <= (int)kitty.x)
	{
		current = (int)left + kitty.offset_x;
		if (current >= 0 && current < PLANE_X)
			draw_slice(data, current, kitty);
		kitty.offset_x++;
	}
}

static t_point	set_cat(t_cbdata *data, int n)
{
	t_point	cat;
	
	cat.x = data->cats[n].pos.x - data->pos_x;
	cat.y = data->cats[n].pos.y - data->pos_y;
	cat.angle = atanf(-cat.y / cat.x);
	if (cat.x < 0)
		cat.angle += M_PI;
	cat.angle = fmod(cat.angle + TWO_PI, TWO_PI);
	cat.dist = sqrt(cat.x * cat.x + cat.y *cat.y);
	return (cat);
}

static t_point	set_screen(t_cbdata *data, t_point cat)
{
	t_point	screen;

	screen.angle = fmod(data->angle - cat.angle + TWO_PI, TWO_PI);
	screen.x = PLANE_X / 2.0 + PROJ_PLAN * tanf(screen.angle);
	return (screen);
}

static t_app_cat	set_app_cat(float angle, float dist)
{
	t_app_cat	kitty;

	kitty.reduct = fabs(1.0 / cosf(angle)) * (PROJ_PLAN / dist);
	kitty.x = SPRITE_L * kitty.reduct;
	kitty.y = SPRITE_H * kitty.reduct;
	kitty.offset_x = 0;
	kitty.offset_y = 0;
	return (kitty);
}
