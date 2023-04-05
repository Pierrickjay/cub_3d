/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:24:08 by pjay              #+#    #+#             */
/*   Updated: 2023/04/05 10:21:34 by rertzer          ###   ########.fr       */
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


int	ft_mapped(t_cbdata *data, char *line)
{
	static int i = 0;

	data->map[i] = ft_strdup(line);
	
	i++;

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

int	find_one(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '1')
		return (1);
	else 
		return (0);
}

int	count_map(char *av)
{
	int 	countmalloc;
	int		fd;
	char	*str;

	countmalloc = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (-1);
	str = get_next_line(fd);
	while (str)
	{
		countmalloc += find_one(str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (count_malloc);
}

int	map_init(t_cbdata *data, int countmalloc)
{
	data->map = malloc(sizeof(data->map) * countmalloc + 1);
	if (data->map == NULL)
		cb_exit(data);
}

void	parse_file(t_cbdata *data, char *av)
{
	int		fd;
	char	*line;
	int		ret;
	int		countmalloc;

	countmalloc = count_map(av);
	if (map_init)
	fd = open(av, O_RDONLY);
	if (fd == -1)
		cb_exit(data);
	line = get_next_line(fd);
	ret = 0;
	while (line)
	{
		if (ret)
			ret = parse_map(line);
		else
		{
			ret = parse_line(data, line);
			if (ret == 1)
				parse_map(line);
		}
		if (ret == -1)
			ft_free_and_close(data, fd, line);

		free(line);
		line = get_next_line(fd);
	}
	//print_strs(data.map);
}





