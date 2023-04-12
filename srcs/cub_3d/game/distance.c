/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:09:40 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/12 15:32:43 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

float	calculate_distance(t_cbdata *data, t_point intersect)
{
	return (sqrt(pow(data->pos_x - intersect.x, 2) + \
				pow(data->pos_y - intersect.y, 2)));
}
