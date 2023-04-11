/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:28:30 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/11 14:42:42 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

bool	point_outofrange(t_cbdata *data, t_point *p)
{
	bool	out;

	out = false;
	if (p->y >= (double)(data->map_y * BLOCK_SIZE) \
			|| p->y <= 0.0 \
			|| p->x <= 0.0 \
			|| p->x >= (double)(data->map_x * BLOCK_SIZE))
	{
		out = true;
		p->x = INFINITY;
		p->y = INFINITY;
	}
	return (out);
}
