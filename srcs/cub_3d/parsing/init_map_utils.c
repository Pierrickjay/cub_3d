/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:01:14 by pjay              #+#    #+#             */
/*   Updated: 2023/04/25 16:24:13 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

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

void	count_map(t_cbdata *data, char *av)
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

	printf("ft_strlen(;ine) = %d\n", (int)ft_strlen(line));
	if (i < data->map_y)
		ft_strlcpy(data->map[i], line, ft_strlen(line));
	if (!data->map[i])
	{
		free(line);
		cb_exit(data, "parse_map error");
	}
	i++;
}
