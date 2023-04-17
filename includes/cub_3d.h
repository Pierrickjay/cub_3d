/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:37:39 by pjay              #+#    #+#             */
/*   Updated: 2023/04/17 15:50:44 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include "libft.h"
# include "get_next_line.h"
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <errno.h>

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT  65361
# define KEY_RIGHT 65363
# define CELL_SOFT	"0NSEW"
# define CELL_MAP	"01NSEW"
# define CELL_START "NSEW"
# define PARSING "NO,SO,WE,EA,F,C"
# define MINI_X	320
# define MINI_Y 200
# define BLOCK_SIZE 64.0
# define PLANE_X 1280.0
# define PLANE_Y 800.0
# define PROJ_PLAN 1108.51251684 // (PLANE_X / 2) / tan(M_PI / 6)
# define ANGLE_PACE M_PI / (3 * PLANE_X)
# define RAY_COLOR 0xFFFF84

# define DP printf("%s %d\n", __FILE__, __LINE__);

enum e_keycode {down, right, right_view};
enum e_card{n, s, e, w, f, c};

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		mini_tile_size;

}	t_image;

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
	float	x;
	float	y;
	float	dist;
	float	angle;
	char	wall;
}	t_point;

typedef struct s_texture
{
	t_img	wall[4];
	t_img	map;
}	t_texture;


typedef struct s_cbdata
{
	char			*texture_file[4];
	char			**map;
	void			*mlx;
	void			*mlx_win;
	int				cf_color[2];
	int				map_x;
	int				map_y;
	float			pos_x;
	float			pos_y;
	float			angle;
	t_point			raycast[1280];
	float			proj_slice_height[1280];
	t_image			image[2];
	t_texture		texture;
	int				img;
	int				keypressed[3];

}	t_cbdata;

int		create_rgb(char *line_color);
bool	parse_line(t_cbdata *data, char *line);
float	calculate_distance(t_cbdata *data, t_point intersect);
bool	point_outofrange(t_cbdata *data, t_point *p);
t_point	get_h_intersect(t_cbdata *data, float angle);
t_point	get_v_intersect(t_cbdata *data, float angle);
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
void	map_init(t_cbdata *data);
void	parse_map(t_cbdata *data, char *line);
void	count_map(t_cbdata *data, char *av);
int		find_one(char *str);
void	init_game(t_cbdata *data);
void	set_hooks(t_cbdata *data);
void	change_pos_player(t_cbdata *data);
void	change_view_player(t_cbdata *data);
bool	bump_wall(t_cbdata *data, int new_x, int new_y);
void	draw_lines(t_cbdata *data);
void	redraw_mini_map(t_cbdata *data);
void	my_mlx_pixel_put(t_cbdata *data, int x, int y, int color);
void	render_3d(t_cbdata *data);
void	load_img(t_cbdata *data/*, t_img *wall*/);
void	draw_ceillinroof(t_cbdata *data);
void	mini_tile_file(t_cbdata *data, int x, int y, int color);
#endif
