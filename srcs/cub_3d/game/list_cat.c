/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:44:32 by pjay              #+#    #+#             */
/*   Updated: 2023/04/26 14:46:14 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

static void set_cat(t_cbdata *data, t_list_cats *cats/*, int n*/)
{
	//t_point	cat;
	(void)n;
	cats->point.x = cats->pos_x - data->pos_x;
	cats->point.y = cats->pos_y - data->pos_y;
	cats->point.angle = atanf( - cats->pos_y / cats->pos_x);
	if (cats->point.y > 0)
		cats->point.angle += M_PI;
	printf("cat angle %f\n", cats->point.angle);
	cats->point.angle = fmod(cats->point.angle + TWO_PI, TWO_PI);
	cats->point.dist = sqrt(cats->point.x * cats->point.x + cats->point.y * cats->point.y);
	//return (cat);
}

// void	print_cat_point(t_list_cats *cats)
// {
// 	while (cats)
// 	{
// 		printf("x = %f y = %f dist = %f angle = %f\n", cats->point.x, cats->point.y, cats->point.dist, cats->point.angle);
// 		cats = cats->next;
// 	}

// }

int	check_if_ordered(t_list_cats *cats)
{
	t_list_cats	*tmp;

	tmp = cats;
	while (cats)
	{
		tmp = cats->next;
		if (cats->point.dist > tmp->point.dist)
			return (-1);
		cats = cats->next;
	}
	return (0);
}

void	swap_value(t_list_cats **tmp, t_list_cats **min)
{
	t_point		tmp_point;
	float		pos_x_tmp;
	float		pos_y_tmp;

	tmp_point = (*tmp)->point;
	pos_x_tmp = (*tmp)->pos_x;
	pos_y_tmp = (*tmp)->pos_y;
	(*tmp)->point = (*min)->point;
	(*tmp)->pos_x = (*min)->pos_x;
	(*tmp)->pos_y = (*min)->pos_y;
	(*min)->point = tmp_point;
	(*min)->pos_x = pos_x_tmp;
	(*min)->pos_y = pos_y_tmp;
}


void	tri_list(t_list_cats *cat)
{
	t_list_cats	*tmp;
	t_list_cats	*tmp2;
	t_list_cats	*min;

	tmp = cat;
	while (tmp)
	{
		tmp2 = tmp;
		min = tmp;
		while (tmp2)
		{
			if (tmp2->point.dist < min->point.dist)
			{
				min = tmp2;
			}
			tmp2 = tmp2->next;
		}
		if (min != tmp)
		{
			swap_value(&tmp, &min);
		}
		tmp = tmp->next;
	}
}

void	arrange_cats_list(t_cbdata *data)
{
	t_list_cats	*tmp;

	tmp = data->cats;
	while (tmp)
	{
		set_cat(data, tmp);
		tmp = tmp->next;
	}
	tri_list(data->cats);
//	print_cat_point(data->cats);
}
