/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 09:10:05 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/05 09:48:20 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

bool	map_check_ok(char **map)
{
	int	i;
	int	j;
	int	size_y;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!map_cell_ok(map, i, j))
				return (0);
		}
	}
	return (1);
}

static bool	map_cell_ok(char **map, int i, int j)
{
	int	ok;

	if (!cell_isa(map[i][j]), CELL_SOFT)
		return (1);
	ok = map_cell_isin(map, i - 1, j);
	ok += map_cell_isin(map, i + 1, j);
	ok += map_cell_isin(map, i, j - 1);
	ok += map_cell_isin(map, i, j + 1);
	if (ok == 4)
		return (1);
	return (0);
}

bool	map_cell_isin(char **map, int i, int j)
{
	if (i < 0 || j < 0 || map[i] == NULL || map[i][j] == '\n')
		return (0);

}

