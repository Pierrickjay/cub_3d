/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:28:30 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/10 11:59:00 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

bool	point_outofrange(t_point *p)
{
	bool	out;
DP
	out = false;
	if (p->x > (double)INT_MAX)
	{
		p->x = (double)INT_MAX;
		out = true;DP
	}
	if (p->x < (double)INT_MIN)
	{
		p->x = (double)INT_MIN;
		out = true;DP
	}
	if (p->y > (double)INT_MAX)
	{
		p->y = (double)INT_MAX;
		out = true;DP
	}
	if (p->y < (double)INT_MIN)
	{
		p->y = (double)INT_MIN;
		out = true;DP
	}
	return (out);
}
