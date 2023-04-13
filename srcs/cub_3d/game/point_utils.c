/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:28:30 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/13 10:40:09 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

bool	point_outofrange(t_cbdata *data, t_point *p)
{
	bool	out;

	out = false;
	if (p->y >= (float)(data->map_y * BLOCK_SIZE) \
			|| p->y <= 0.0 \
			|| p->x <= 0.0 \
			|| p->x >= (float)(data->map_x * BLOCK_SIZE))
	{
		out = true;
		p->x = INFINITY;
		p->y = INFINITY;
	}
	return (out);
}
