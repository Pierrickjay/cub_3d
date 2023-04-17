/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:01:35 by pjay              #+#    #+#             */
/*   Updated: 2023/04/17 09:01:59 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"


int	ft_search_string(char *str, char *cmp)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (cmp[y] == '\0' && str[i] == '\0')
		return (1);
	while (str[i])
	{
		while (str[i + y] == cmp[y] && str[i + y] && cmp[y])
			y++;
		if (cmp[y] == '\0' && str[i + y] == '\0')
			return (1);
		else
			y = 0;
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_cbdata	data;

	if (!env || !*env)
		return (0);
	if (ac != 2 || ft_search_string(av[1], ".cub") != 1)
	{
		printf("Error\nWe need only two parameters and the map");
		printf("need to have a .cub extension\n");
		return (0);
	}
	init_data(&data);
	parse_file(&data, av[1]);
	init_game(&data);
}
