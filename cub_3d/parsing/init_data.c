/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:33:14 by pjay              #+#    #+#             */
/*   Updated: 2023/04/04 16:05:31 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	init_data(t_cbdata *data)
{
	data->map = NULL;
}

void	cb_exit(t_cbdata *data)
{
	ft_free_strs(data->map);
	ft_free((void **)&data->E_file);
	ft_free((void **)&data->W_file);
	ft_free((void **)&data->N_file);
	ft_free((void **)&data->S_file);
}
