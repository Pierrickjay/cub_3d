/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 09:10:05 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/17 10:26:15 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static bool	map_cell_ok(char **map, int i, int j);
static bool	map_cell_isin(char **map, int i, int j);

void	map_set_start(t_cbdata *data, int i, int j)
{
	data->pos_x = (float)(j * BLOCK_SIZE + BLOCK_SIZE / 2);
	data->pos_y = (float)(i * BLOCK_SIZE  + BLOCK_SIZE / 2);
	if (data->map[i][j] == 'N')
		data->angle = M_PI_2;
	else if (data->map[i][j] == 'E')
		data->angle = 0.0;
	else if (data->map[i][j] == 'W')
		data->angle = M_PI;
	else
		data->angle = 3.0 * M_PI_2;
}

bool	map_check_ok(t_cbdata *data)
{
	int	i;
	int	j;
	int	start;

	start = 0;
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (!map_cell_ok(data->map, i, j))
				return (0);
			if (cell_isa(data->map[i][j], CELL_START))
			{
				if (start)
					cb_exit(data, "Invalid map");
				start = 1;
				map_set_start(data, i, j);
			}
		}
	}
	return (1);
}

static bool	map_cell_ok(char **map, int i, int j)
{
	int	ok;

	if (!cell_isa(map[i][j], CELL_SOFT))
		return (1);
	ok = map_cell_isin(map, i - 1, j);
	ok += map_cell_isin(map, i + 1, j);
	ok += map_cell_isin(map, i, j - 1);
	ok += map_cell_isin(map, i, j + 1);
	if (ok == 4)
		return (1);
	return (0);
}

static bool	map_cell_isin(char **map, int i, int j)
{
	if (i < 0 || j < 0 || map[i] == NULL || map[i][j] == '\0' \
		|| !cell_isa(map[i][j], CELL_MAP))
		return (0);
	return (1);
}
