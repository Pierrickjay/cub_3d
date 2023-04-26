/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_cats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:37:29 by pjay              #+#    #+#             */
/*   Updated: 2023/04/26 18:49:43 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d_bonus.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del || !lst)
		return ;
	if (lst)
	{
		free(lst);
	}
}

void	ft_lstclear_cats(t_list_cats **lst, void (*del)(void*))
{
	t_list_cats	*in;

	if (!del || !*lst || !del)
		return ;
	while (*lst)
	{
		in = (*lst)->next;
		free(*lst);
		*lst = in;
	}
	free(*lst);
	*lst = NULL;
}
