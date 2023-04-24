/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:22:42 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/24 17:43:46 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"
#include "cub_3d_bonus.h"

void	cat_init(t_cbdata *data, int x, int y)
{
	data->cats->pos.x = x * BLOCK_SIZE - BLOCK_SIZE / 2;
	data->cats->pos.y = y * BLOCK_SIZE - BLOCK_SIZE / 2;
}
