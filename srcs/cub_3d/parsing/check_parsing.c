/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:58:22 by pjay              #+#    #+#             */
/*   Updated: 2023/04/12 17:53:00 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

int	check_player_p(char **str)
{
	int	i;
	int	j;
	int	diff;

	i = -1;
	diff = 0;
	while (str[++i])
	{
		j = -1;
		while (++j < (int)ft_strlen(str[i]))
		{
			if (str[i][j] == 'N' || str[i][j] == 'S' ||
				str[i][j] == 'E' || str[i][j] == 'W')
				diff++;
		}
	}
	if (diff != 1)
		return (1);
	return (0);
}
