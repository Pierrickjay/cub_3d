/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:46:18 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/27 09:27:04 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

static bool	map_cell_ok(char **map, int i, int j);
static bool	map_cell_isin(char **map, int i, int j);
static void	map_set_things(t_cbdata *data, int i, int j);

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
			}
			if (cell_isa(data->map[i][j], CELL_THINGS))
				map_set_things(data, i, j);
		}
	}
	print_cats_pos(data->cats);
	return (1);
}

static bool	map_cell_ok(char **map, int i, int j)
{
	int	ok;

	if (!(cell_isa(map[i][j], CELL_MAP_BONUS) || map[i][j] == ' '))
		return (0);
	if (!cell_isa(map[i][j], CELL_SOFT_BONUS))
		return (1);
	ok = map_cell_isin(map, i - 1, j);
	ok += map_cell_isin(map, i + 1, j);
	ok += map_cell_isin(map, i, j - 1);
	ok += map_cell_isin(map, i, j + 1);
	if (ok == 4)
		return (1);
	return (0);
}

static void	map_set_things(t_cbdata *data, int i, int j)
{
	if (data->map[i][j] != 'M')
	{
		data->pos_x = (float)(j * BLOCK_SIZE + BLOCK_SIZE / 2);
		data->pos_y = (float)(i * BLOCK_SIZE + BLOCK_SIZE / 2);
	}
	if (data->map[i][j] == 'N')
		data->angle = M_PI_2;
	else if (data->map[i][j] == 'E')
		data->angle = 0.0;
	else if (data->map[i][j] == 'W')
		data->angle = M_PI;
	else if (data->map[i][j] == 'S')
		data->angle = 3.0 * M_PI_2;
	else
		cat_init(data, j, i);
}

static bool	map_cell_isin(char **map, int i, int j)
{
	if (i < 0 || j < 0 || map[i] == NULL || map[i][j] == '\0' \
		|| !cell_isa(map[i][j], CELL_MAP_BONUS))
		return (0);
	return (1);
}
