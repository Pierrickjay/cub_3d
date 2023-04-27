/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:35:49 by pjay              #+#    #+#             */
/*   Updated: 2023/04/27 10:41:39 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	ft_free(void **ptr)
{
	if (ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_free_strs(char **strs)
{
	size_t	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			ft_free((void **)&strs[i]);
			i++;
		}
		ft_free((void **)&strs);
	}
}

void	ft_free_and_close(t_cbdata *data, int fd, char *str)
{
	close(fd);
	free(str);
	cb_exit(data, "Parsing error");
}

void	ft_end_and_close(t_cbdata *data, int fd, char *line)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	cb_exit(data, "Parsing error");
}

void	ft_tripple_free_mlx(char *str, char *str2, char *str3, t_cbdata *data)
{
	free(str);
	free(str2);
	free(str3);
	cb_exit(data, "MLX_FAILED");
}
