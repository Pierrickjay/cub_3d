/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:09:40 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/12 15:07:10 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

double	calculate_distance(t_cbdata *data, t_point intersect)
{
	return (sqrt(pow(data->pos_x - intersect.x, 2.0) + \
				pow(data->pos_y - intersect.y, 2.0)));
}
