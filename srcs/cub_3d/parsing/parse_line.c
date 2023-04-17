/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:12:29 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/17 17:32:28 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static bool	parse_token(t_cbdata *data, char **token);
static char	**get_key(t_cbdata *data, char **token);
static int	set_texture_file(t_cbdata *data, char *token, int i, char **key);
static int	set_color(t_cbdata *data, char **token, int i, char **key);

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
	tok_nb = 0;
	while (token[tok_nb])
		tok_nb++;
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

	key = get_key(data, token);
	i = -1;
	while (++i < 4)
	{
		if (ft_strcmp(token[0], key[i]) == 0)
			return (set_texture_file(data, token[1], i, key));
	}
	i = -1;
	while (++i < 2)
	{
		if (ft_strcmp(token[0], key[i + 4]) == 0)
			return (set_color(data, token, i, key));
	}
	ft_free_strs(key);
	return (-1);
}

static char	**get_key(t_cbdata *data, char **token)
{
	char	**key;

	key = ft_split(PARSING, ',');
	if (key == NULL)
	{
		ft_free_strs(token);
		cb_exit(data, "Malloc error");
	}
	return (key);
}

static int	set_texture_file(t_cbdata *data, char *token, int i, char **key)
{
	data->texture_file[i] = ft_strdup(token);
	data->texture_file[i][ft_strlen(token) - 1] = 0;
	ft_free_strs(key);
	return (0);
}

static int	set_color(t_cbdata *data, char **token, int i, char **key)
{
	data->cf_color[i] = create_rgb(token[1]);
	if (data->cf_color[i] == -1)
	{
		ft_free_strs(key);
		ft_free_strs(token);
		cb_exit(data, "Invalid color");
	}
	ft_free_strs(key);
	return (0);
}
