/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:01:14 by pjay              #+#    #+#             */
/*   Updated: 2023/04/12 10:49:02 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
//si il y a des tabs a la place des espaces dans la map ca segault
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

void	count_map(t_cbdata * data, char *av)
{
	int		fd;
	int		len;
	char	*str;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		cb_exit(data, "open file failed");
	str = get_next_line(fd);
	while (str)
	{
		if (find_one(str))
		{
			data->map_y++;
			len = ft_strlen(str) - 1;
			if (len > data->map_x)
				data->map_x = len;
		}
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
}

void	map_init(t_cbdata *data)
{
	int	i;

	data->map = ft_calloc(sizeof(data->map), data->map_y + 1);
	if (data->map == NULL)
		cb_exit(data, "Malloc failed");
	i = -1;
	while (++i < data->map_y)
	{
		data->map[i] = ft_calloc(data->map_x + 1, sizeof(char));
		if (data->map[i] == NULL)
			cb_exit(data, "Malloc failed");
	}
}

void	parse_map(t_cbdata *data, char *line)
{
	static int	i = 0;

	ft_strlcpy(data->map[i], line, ft_strlen(line));
	if (!data->map[i])
	{
		free(line);
		cb_exit(data, "Malloc failed");
	}
	i++;
}

int	create_rgb(char *line_color)
{
	int		color;
	int		i;
	char	**split_color;

	split_color = ft_split(line_color, ',');
	if (!split_color)
		return (-1);
	i = -1;
	while (split_color[++i]);
	if (i != 3)
	{
		ft_free_strs(split_color);
		return (-1);
	}
	i = -1;
	while (split_color[2][++i])
	{
		if (split_color[2][i] == '\n')
			split_color[2][i] = '\0';
	}
	color = 0; 
	if ((ft_strlen(split_color[0]) > 3) || !ft_all_isdigit(split_color[0]) 
		|| ft_strlen(split_color[1]) > 3 || !ft_all_isdigit(split_color[1])
		|| ft_strlen(split_color[2]) > 3 || !ft_all_isdigit(split_color[2]))
	{
		ft_free_strs(split_color);
		return (-1);
	}
	printf("color 1 = %d, color 2 = %d, colr 3 = %d\n", ft_atoi(split_color[0]), ft_atoi(split_color[1]), ft_atoi(split_color[2]));
	color += ft_atoi(split_color[0]) << 16 | ft_atoi(split_color[1]) << 8
		| ft_atoi(split_color[2]);
	ft_free_strs(split_color);
	return (color);
}
