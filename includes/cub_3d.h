/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:37:39 by pjay              #+#    #+#             */
/*   Updated: 2023/04/05 11:05:20 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include <stdbool.h>

# define	CELL_SOFT	"0NSEO"
# define	CELL_MAP	"01NSEO"

typedef struct s_cbdata
{
	char	*n_file;
	char	*s_file;
	char	*e_file;
	char	*w_file;
	int		ceiling_color;
	int		floor_color;
	char	**map;

}t_cbdata;

void	init_data(t_cbdata *data);
char	**ft_mapped(int fd);
void	print_strs(char **strs);
void	parse_file(t_cbdata *data, char *av);
void	ft_free_strs(char **strs);
void	ft_free_and_close(t_cbdata *data, int fd, char *str);
void	ft_free(void **ptr);
void	cb_exit(t_cbdata *data, char *err_msg);
bool	cell_isa(char c, char *set);
bool	map_check_ok(char **map);
int		create_rgb(char *line_color);
void	map_init(t_cbdata *data, int countmalloc);
void	parse_map(t_cbdata *data, char *line);
int		count_map(char *av);
int		find_one(char *str);
#endif
