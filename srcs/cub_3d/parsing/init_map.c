/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:24:08 by pjay              #+#    #+#             */
/*   Updated: 2023/04/11 15:36:18 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub_3d.h"
bool	parse_line(t_cbdata *data, char *line)
{
	int		len;
	char	**token;

	if (find_one(line) == 1)
		return (1);
	else if (line[0] == '\n')
		return (0);

	len = ft_strlen(line);
	token = ft_split(line, ' ');
	if (ft_strcmp(token[0], "NO") == 0)
		data->n_file = ft_strdup(token[1]);
	else if (ft_strcmp(token[0], "SO") == 0)
		data->s_file = ft_strdup(token[1]);
	else if (ft_strcmp(token[0], "WE") == 0)
		data->w_file = ft_strdup(token[1]);
	else if (ft_strcmp(token[0], "EA") == 0)
		data->e_file = ft_strdup(token[1]);
	else if (ft_strcmp(token[0], "F") == 0)
		data->floor_color = create_rgb(token[1]);
	else if (ft_strcmp(token[0], "C") == 0)
		data->ceiling_color = create_rgb(token[1]);
	else
		return (ft_free_strs(token), -1);
	return (ft_free_strs(token), 0);
}

void	parse_file_2(t_cbdata *data, int fd)
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

void	parse_file(t_cbdata *data, char *av)
{
	int		fd;

	count_map(data, av);
	map_init(data);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		cb_exit(data, "open file failed");
	parse_file_2(data, fd);
	if (!map_check_ok(data))
	{
		close(fd);
		cb_exit(data, "Invalid map");
	}
	data->mini[0].mini_tile_size = ft_min(MINI_X / data->map_x, \
		MINI_Y / data->map_y);
	data->mini[1].mini_tile_size = ft_min(MINI_X / data->map_x, \
		MINI_Y / data->map_y);
	print_strs(data->map);
	printf("n _ file = %s", data->n_file);
	printf("s _ file = %s", data->s_file);
	printf("w _ file = %s", data->w_file);
	printf("e _ file = %s", data->e_file);
	printf("color ceiling = %d\n", data->ceiling_color);
	printf("floor color = %d\n", data->floor_color);
	close(fd);
}
