/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 11:35:25 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/04 12:29:36 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cbdata	data;

	if (argc != 2)
		error_exit(&data, NO_ARG);
	init_data(&data);
	init_map(&data, argv[1]);
	check_map(&data);
	init_game(&data);
}
