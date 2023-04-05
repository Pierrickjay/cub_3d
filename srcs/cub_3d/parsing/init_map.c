/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:24:08 by pjay              #+#    #+#             */
/*   Updated: 2023/04/04 16:06:15 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	print_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		printf("%s\n", strs[i]);
		i++;
	}
}

int	create_rgb(char *line_color)
{
	int		color;
	char	**split_color;

	split_color = ft_split(line_color, ',');
	if (!split_color)
		return (-1);
	color = 0;
	color += ft_atoi(split_color[0]) << 16 | ft_atoi(split_color[1]) << 8
		| ft_atoi(split_color[2]);
	return (color);
}


char	**ft_mapped(int fd)
{
	char	*mappedmap;
	char	*bufferstr;
	char	**splitted;
	int		i;

	i = 0;
	mappedmap = malloc(sizeof(char));
	mappedmap[0] = '\0';
	while (i == 0 || mappedmap != NULL)
	{
		bufferstr = get_next_line(fd);
		if (bufferstr == NULL)
			break ;
		mappedmap = ft_strjoin(mappedmap, bufferstr);
		i++;
	}
	splitted = ft_split(mappedmap, '\n');
	i = 0;
	free(mappedmap);
	free(bufferstr);
	return (splitted);
}

bool	parse_line(t_cbdata *data, char *line)
{
	int		len;
	char	**token;

	if (line[0] == '1')
		return (1);
	else if (line[0] == '\n')
		return (0);

	len = ft_strlen(line);
	token = ft_split(line, ' ');
	if (ft_strcmp(token[0], "NO") == 0)
		data->N_file = ft_strdup(token[1]);
	else if (ft_strcmp(token[0], "SO") == 0)
		data->S_file = ft_strdup(token[1]);
	else if (ft_strcmp(token[0], "WE") == 0)
		data->W_file = ft_strdup(token[1]);
	else if (ft_strcmp(token[0], "EA") == 0)
		data->E_file = ft_strdup(token[1]);
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

	fd = open(av, O_RDONLY);
	if (fd == -1)
		cb_exit(data);
	line = get_next_line(fd);
	while (line)
	{
		ret = parse_line(data, line);
		if (ret == -1)
			ft_free_and_close(data, fd, );
		free(line);
		line = get_next_line(fd);
	}
	//print_strs(data.map);
}





