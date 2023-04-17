/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:12:29 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/17 13:48:21 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub_3d.h"

static bool	parse_token(t_cbdata *data, char **token);

bool	parse_line(t_cbdata *data, char *line)
{
	int		tok_nb;
	bool	ret;
	char	**token;

	if (find_one(line) == 1)
		return (1);
	else if (line[0] == '\n')
		return (0);

	token = ft_split(line, ' ');
	tok_nb = -1;
	while (token[++tok_nb]);
	if (tok_nb != 2)
	{
		ft_free_strs(token);
		cb_exit(data, "Invalid map");
	}
	ret = parse_token(data, token);
	ft_free_strs(token);
	return (ret);
}

static bool	parse_token(t_cbdata *data, char **token)
{
	int			i;
	char		**key;

	key = ft_split(PARSING, ',');
	if (key == NULL)
	{
		ft_free_strs(token);
		cb_exit(data, "Malloc error");
	}
	i = -1;
	while (++i < 4)
	{
		if (ft_strcmp(token[0], key[i]) == 0)
		{
			data->texture_file[i] = ft_strdup(token[1]);
			data->texture_file[i][ft_strlen(token[1]) - 1] = 0;
			return (0);
		}
	}
	while (i < 6)
	{
		if (ft_strcmp(token[0], key[i]) == 0)
		{
			data->cf_color[i - 4] = create_rgb(token[1]);
			if (data->cf_color[i - 4] == -1)
			{
				ft_free_strs(token);
				cb_exit(data, "Invalid color");
			}
			return (0);
		}
		i++;
	}
	return (-1);
}
