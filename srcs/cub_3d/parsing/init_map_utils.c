/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:01:14 by pjay              #+#    #+#             */
/*   Updated: 2023/04/05 14:58:33 by pjay             ###   ########.fr       */
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

int	count_map(char *av)
{
	int		countmalloc;
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
		//printf("count malloc= %d of str %s", countmalloc, str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	printf("count malloc= %d\n", countmalloc);
	return (countmalloc);
}

void	map_init(t_cbdata *data, int countmalloc)
{
	data->map = ft_calloc(sizeof(data->map), countmalloc + 1);
	if (data->map == NULL)
		cb_exit(data, "Malloc failed");
}

void	parse_map(t_cbdata *data, char *line)
{
	static int	i = 0;
	

	data->map[i] = ft_strdup(line);
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
	char	**split_color;

	split_color = ft_split(line_color, ',');
	if (!split_color)
		return (-1);
	color = 0;
	printf("color 1 = %d, color 2 = %d, colr 3 = %d\n", ft_atoi(split_color[0]), ft_atoi(split_color[1]), ft_atoi(split_color[2]));
	color += ft_atoi(split_color[0]) << 16 | ft_atoi(split_color[1]) << 8
		| ft_atoi(split_color[2]);
	ft_free_strs(split_color);
	return (color);
}
