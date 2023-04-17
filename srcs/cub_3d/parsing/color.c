/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:41:04 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/17 17:23:57 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static char	**get_split_color(char *line_color);
static int	rgb_error(char **str);

int	create_rgb(char *line_color)
{
	int		color;
	int		rgb;
	int		i;
	char	**split_color;

	split_color = get_split_color(line_color);
	if (split_color == NULL)
		return (-1);
	if (!ft_all_isdigit(split_color[0]) || !ft_all_isdigit(split_color[1]) \
			|| !ft_all_isdigit(split_color[2]))
		return (rgb_error(split_color));
	rgb = 0;
	i = -1;
	while (++i < 3)
	{
		color = ft_atoi(split_color[i]);
		printf("color %d is %d\n", i, color);
		if (color < 0 || color > 255)
			return (rgb_error(split_color));
		rgb |= color << (16 - i * 8);
	}
	ft_free_strs(split_color);
	return (rgb);
}

static char	**get_split_color(char *line_color)
{
	int		i;
	char	**split_color;

	split_color = ft_split(line_color, ',');
	if (!split_color)
		return (NULL);
	i = 0;
	while (split_color[i])
		i++;
	if (i != 3)
	{
		ft_free_strs(split_color);
		return (NULL);
	}
	i = -1;
	while (split_color[2][++i])
	{
		if (split_color[2][i] == '\n')
			split_color[2][i] = '\0';
	}
	return (split_color);
}

static int	rgb_error(char **str)
{
	ft_free_strs(str);
	return (-1);
}
