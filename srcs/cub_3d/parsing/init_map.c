/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:24:08 by pjay              #+#    #+#             */
/*   Updated: 2023/04/05 17:00:34 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	print_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		printf("%s", strs[i]);
		i++;
	}
}



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
	{
		ft_free_strs(token);
		return (-1);
	}
	ft_free_strs(token);
	return (0);
}

void	parse_file(t_cbdata *data, char *av)
{
	int		fd;
	char	*line;
	int		ret;
	int		strlen_max;
	int		tmp_len;
	int		countmalloc;

	strlen_max = 0;
	tmp_len = 0;
	countmalloc = count_map(av);
	map_init(data, countmalloc);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		cb_exit(data, "open file failed");
	line = get_next_line(fd);
	ret = 0;
	while (line)
	{
		if (ret)
		{
			parse_map(data, line);
			tmp_len = ft_strlen(line);
			if (tmp_len > strlen_max)
				strlen_max = tmp_len;
		}
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
	if (!map_check_ok(data))
		cb_exit(data, "Invalid map");
	data->mini.mini_tile_size = ft_min(MINI_X / strlen_max, MINI_Y / countmalloc);
	print_strs(data->map);
	printf("n _ file = %s", data->n_file);
	printf("s _ file = %s", data->s_file);
	printf("w _ file = %s", data->w_file);
	printf("e _ file = %s", data->e_file);
	printf("color ceiling = %d\n", data->ceiling_color);
	printf("floor color = %d\n", data->floor_color);
}





