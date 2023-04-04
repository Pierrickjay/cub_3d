/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:04:42 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/04 12:37:50 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	error_exit(t_cbdata *data, char *msg)
{		
	ft_printf("Error\n%s\n", msg);
	clean_exit(data, 1);
}

void	clean_exit(t_cbdata *data, int status)
{
	clean_map(data->map.map, data->map.size_y);
	exit(status);
}

void	clean_map(char **map, size_t size_y)
{
	size_t	i;

	i = -1;
	if (NULL == map)
		return ;
	while (++i < size_y)
	{
		if (NULL == map[i])
			break ;
		free(map[i]);
	}
	free(map);
}
