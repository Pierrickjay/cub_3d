/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:24:08 by pjay              #+#    #+#             */
/*   Updated: 2023/04/13 08:55:57 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub_3d.h"

bool	parse_line(t_cbdata *data, char *line)
{
	int		tok_nb;
	char	**token;

	if (find_one(line) == 1)
		return (1);
	else if (line[0] == '\n')
		return (0);

	token = ft_split(line, ' ');
	tok_nb = -1;
	while (token[++tok_nb]);
	if (tok_nb != 2)
		cb_exit(data, "Invalid map");
	if (ft_strcmp(token[0], "NO") == 0)
	{
		data->n_file = ft_strdup(token[1]);
		data->n_file[ft_strlen(token[1]) - 1] = 0;
	}
	else if (ft_strcmp(token[0], "SO") == 0)
	{
		data->s_file = ft_strdup(token[1]);
		data->s_file[ft_strlen(token[1]) - 1] = 0;
	}
	else if (ft_strcmp(token[0], "WE") == 0)
	{
		data->w_file = ft_strdup(token[1]);
		data->w_file[ft_strlen(token[1]) - 1] = 0;
	}
	else if (ft_strcmp(token[0], "EA") == 0)
	{
		data->e_file = ft_strdup(token[1]);
		data->e_file[ft_strlen(token[1]) - 1] = 0;
	}
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
	printf("\nmap x %d, map y %d tile %d\n", data->map_x, data->map_y, data->mini[0].mini_tile_size);
	printf("\nn _ file = %s\n", data->n_file);
	printf("s _ file = %s\n", data->s_file);
	printf("w _ file = %s\n", data->w_file);
	printf("e _ file = %s\n", data->e_file);
	printf("color ceiling = %d\n", data->ceiling_color);
	printf("floor color = %d\n", data->floor_color);
	close(fd);
}
