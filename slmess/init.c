/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:18:26 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/04 12:49:16 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	init_map(t_cbdata *data, char *filename)
{
	int		fd;

	check_filename(data, filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit(data, strerror(errno));
	load_map(data, fd);
	close(fd);
}

void	init_data(t_cbdata *data)
{
}

void	check_filename(t_cbdata *data, char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (NULL == ext || ft_strncmp(ext, ".cub", 5))
		error_exit(sldata, CUB);
}
