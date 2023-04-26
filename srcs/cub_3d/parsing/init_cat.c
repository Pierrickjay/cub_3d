/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:22:42 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/26 14:57:44 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

void	cat_init(t_cbdata *data, int x, int y)
{
	t_list_cats	*maillon;

	maillon = ft_lstnew_cats((float)(x * BLOCK_SIZE + BLOCK_SIZE / 2), \
		(float)(y * BLOCK_SIZE + BLOCK_SIZE / 2));
	if (maillon == NULL)
		cb_exit(data, "MALLOC FAILED");
	data->nb_cats++;
	ft_lstadd_back_cats(&data->cats, maillon);
}


