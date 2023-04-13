/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:09:40 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/13 14:01:07 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

float	calculate_distance(t_cbdata *data, t_point intersect)
{
	return (sqrt(powf(data->pos_x - intersect.x, 2.0) + \
				powf(data->pos_y - intersect.y, 2.0)));
}
