/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:24:08 by pjay              #+#    #+#             */
/*   Updated: 2023/04/24 09:45:03 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static void	parse_file_line(t_cbdata *data, int fd);

void	parse_file(t_cbdata *data, char *av)
{
	int		fd;

	count_map(data, av);
	map_init(data);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		cb_exit(data, "open file failed");
	parse_file_line(data, fd);
	if (!map_check_ok(data))
	{
		close(fd);
		cb_exit(data, "Invalid map");
	}
	data->image[0].mini_tile_size = ft_min(MINI_X / data->map_x, \
		MINI_Y / data->map_y);
	data->image[1].mini_tile_size = ft_min(MINI_X / data->map_x, \
		MINI_Y / data->map_y);
	close(fd);
}

static void	parse_file_line(t_cbdata *data, int fd)
{
	char	*line;
	int		ret;

	ret = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ret)
			parse_map(data, line);
		else
		{
			ret = parse_line(data, line);
			if (ret == 1)
				continue ;
		}
		if (ret == -1)
			ft_free_and_close(data, fd, line);
		free(line);
		line = get_next_line(fd);
	}
}
