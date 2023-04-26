/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:25:32 by pjay              #+#    #+#             */
/*   Updated: 2023/04/26 16:43:10 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

static t_point		set_screen(t_cbdata *data, t_list_cats *cat);
static t_app_cat	set_app_cat(float angle, float dist);

void	put_cat(t_cbdata *data)
{
	t_list_cats	*cat;
	t_app_cat	kitty;
	int			current;
	float		left;
	t_point		screen;

	arrange_cats_list(data);
	cat = data->cats;
	while (cat)
	{
		screen = set_screen(data, cat);
		if (!(screen.angle > M_PI_2 && screen.angle < 3 * M_PI_2))
		{
			kitty = set_app_cat(screen.angle, cat->point.dist);
			left = screen.x - kitty.x / 2.0;
			while (kitty.offset_x <= (int)kitty.x)
			{
				current = (int)left + kitty.offset_x;
				if (current >= 0 && current < PLANE_X \
                && !(data->raycast[current].dist < cat->point.dist))
					draw_slice(data, current, kitty);
				kitty.offset_x++;
			}
		}
		cat = cat->next;
	}
}

static t_point	set_screen(t_cbdata *data, t_list_cats *cat)
{
	t_point	screen;

	screen.angle = fmod(data->angle - cat->point.angle + TWO_PI, TWO_PI);
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
