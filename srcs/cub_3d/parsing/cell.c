/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 09:30:10 by rertzer           #+#    #+#             */
/*   Updated: 2023/05/01 09:48:09 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

bool	cell_isa(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

bool	cell_inside(t_cbdata *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map_x || y >= data->map_y)
		return (false);
	return (true);
}
