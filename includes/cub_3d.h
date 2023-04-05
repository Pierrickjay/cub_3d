/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:37:39 by pjay              #+#    #+#             */
/*   Updated: 2023/04/05 15:30:23 by pjay             ###   ########.fr       */
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
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>

# define CELL_SOFT	"0NSEO"
# define CELL_MAP	"01NSEO"
# define MINI_X	1280 //320
# define MINI_Y	800//200

typedef struct s_minimap
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		size_tile;
	int		mini_tile_size;
}	t_minimap;

typedef struct s_cbdata
{
	char		*n_file;
	char		*s_file;
	char		*e_file;
	char		*w_file;
	int			ceiling_color;
	int			floor_color;
	char		**map;
	void		*mlx;
	void		*mlx_win;
	t_minimap	mini;

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
void	init_game(t_cbdata *data);
void	set_hooks(t_cbdata *data);

#endif
