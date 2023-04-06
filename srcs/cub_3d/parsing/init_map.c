/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:24:08 by pjay              #+#    #+#             */
/*   Updated: 2023/04/06 11:24:23 by pjay             ###   ########.fr       */
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

void	parse_file_2_utils(t_cbdata *data, char *line \
	, int *tmp_len, int *strlen_max)
{
	parse_map(data, line);
	*tmp_len = ft_strlen(line);
	if (*tmp_len > *strlen_max)
		*strlen_max = *tmp_len;
}

int	parse_file_2(t_cbdata *data, int fd)
{
	char	*line;
	int		ret;
	int		strlen_max;
	int		tmp_len;

	ret = 0;
	strlen_max = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ret)
			parse_file_2_utils(data, line, &tmp_len, &strlen_max);
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
	return (strlen_max);
}

void	parse_file(t_cbdata *data, char *av)
{
	int		fd;
	int		countmalloc;
	int		strlen_max;

	countmalloc = count_map(av);
	map_init(data, countmalloc);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		cb_exit(data, "open file failed");
	strlen_max = parse_file_2(data, fd);
	if (!map_check_ok(data))
	{
		close(fd);
		cb_exit(data, "Invalid map");
	}
	data->mini[0].mini_tile_size = ft_min(MINI_X / strlen_max, \
		MINI_Y / countmalloc);
	data->mini[1].mini_tile_size = ft_min(MINI_X / strlen_max, \
		MINI_Y / countmalloc);
	print_strs(data->map);
	printf("n _ file = %s", data->n_file);
	printf("s _ file = %s", data->s_file);
	printf("w _ file = %s", data->w_file);
	printf("e _ file = %s", data->e_file);
	printf("color ceiling = %d\n", data->ceiling_color);
	printf("floor color = %d\n", data->floor_color);
	close(fd);
}





