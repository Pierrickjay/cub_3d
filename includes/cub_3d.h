/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:37:39 by pjay              #+#    #+#             */
/*   Updated: 2023/04/04 16:05:39 by pjay             ###   ########.fr       */
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

typedef struct s_cbdata
{
	char	*N_file;
	char	*S_file;
	char	*E_file;
	char	*W_file;
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
void	cb_exit(t_cbdata *data);
#endif
