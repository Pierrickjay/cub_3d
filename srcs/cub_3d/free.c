/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:35:49 by pjay              #+#    #+#             */
/*   Updated: 2023/04/04 16:02:34 by pjay             ###   ########.fr       */
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
	while (strs[i])
	{
		ft_free((void **)&strs[i]);
		i++;
	}
	ft_free((void **)&strs);
}


void	ft_free_and_close(t_cbdata *data, int fd, char *str)
{
	close(fd);
	free(str);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd("Parsing error", 2);
	cb_exit(data);
}
