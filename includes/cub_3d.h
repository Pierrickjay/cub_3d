/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:37:39 by pjay              #+#    #+#             */
/*   Updated: 2023/04/11 15:15:49 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <errno.h>

# define CELL_SOFT	"0NSEW"
# define CELL_MAP	"01NSEW"
# define CELL_START "NSEW"
# define MINI_X	320
# define MINI_Y	200
# define BLOCK_SIZE 64
# define PLANE_X 1280
# define PLANE_Y 800
# define ANGLE_PACE 0.000818123 //M_PI / (3 * PLANE_X)
# define PROJ_PLAN 1108.51251684 // MINI_X / 2 - tan(M_PI / 6)
# define DP printf("%s %d\n", __FILE__, __LINE__);

enum e_keycode {up, down, left, right};
typedef struct s_minimap
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		mini_tile_size;

}	t_minimap;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		heigth;
}	t_img;
typedef	struct	s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_texture
{
	t_img	wall_n;
	t_img	wall_e;
	t_img	wall_s;
	t_img	wall_w;
}	t_texture;


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
	int			pos_x;
	int			pos_y;
	double		angle;
	int			redraw;
	double		all_dist[1280];
	double		proj_slic_height[1280];
	t_minimap	mini[2];
	t_texture	texture;
	int			mini_img;

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
bool	map_check_ok(t_cbdata *data);
int		create_rgb(char *line_color);
void	map_init(t_cbdata *data, int countmalloc);
void	parse_map(t_cbdata *data, char *line);
int		count_map(char *av);
int		find_one(char *str);
void	init_game(t_cbdata *data);
void	set_hooks(t_cbdata *data);
void	change_pos_player(t_cbdata *data, enum e_keycode move);
bool	bump_wall(t_cbdata *data, int new_x, int new_y);
void	draw_lines(t_cbdata *data);
void	redraw_mini_map(t_cbdata *data);
void	my_mlx_pixel_put(t_cbdata *data, int x, int y, int color);
void	render_3d(t_cbdata *data);
void	load_img(t_cbdata *data/*, t_img *wall*/);
#endif
