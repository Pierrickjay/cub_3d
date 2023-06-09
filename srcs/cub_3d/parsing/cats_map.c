/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cats_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 10:05:13 by pjay              #+#    #+#             */
/*   Updated: 2023/04/27 12:19:26 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

t_list_cats	*ft_lstnew_cats(float pos_x, float pos_y)
{
	t_list_cats	*maillon;

	maillon = ft_calloc(sizeof(*maillon), 1);
	if (!maillon)
		return (NULL);
	maillon->next = NULL;
	maillon->pos_x = pos_x;
	maillon->pos_y = pos_y;
	maillon->seen = false;
	maillon->point.x = 0;
	maillon->point.y = 0;
	maillon->point.dist = 0;
	maillon->point.angle = 0;
	maillon->point.wall = 0;
	return (maillon);
}

t_list_cats	*ft_lstlast_cats(t_list_cats *lst)
{
	if (lst)
	{
		while (lst)
		{
			if (!lst->next)
				return (lst);
			lst = lst->next;
		}
		return (lst);
	}
	else
	{
		return (NULL);
	}
}

void	ft_lstadd_back_cats(t_list_cats **lst, t_list_cats *new)
{
	t_list_cats	*in;

	if (lst != NULL)
	{
		if (*lst != NULL)
		{
			in = ft_lstlast_cats(*lst);
			in->next = new;
		}
		else
			*lst = new;
	}
}
