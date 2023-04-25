/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:37:39 by pjay              #+#    #+#             */
/*   Updated: 2023/04/25 17:18:36 by pjay             ###   ########.fr       */
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
# define LITTLE_RIGHT	1
# define HALF_RIGHT		2
# define MOUSE_LEFT		3
# define LITTLE_LEFT	11
# define HALF_LEFT		22
# define MOUSE_RIGHT	33
# define MOUSE_CENTER	0
# define SPRITE_H		32
# define SPRITE_L		31
# define CELL_SOFT	"0NSEW"
# define CELL_MAP	"01NSEW"
# define CELL_START "NSEW"
# define PARSING "NO,SO,WE,EA,F,C"
# define MINI_X	320
# define MINI_Y 200
# define BLOCK_SIZE 64
# define PLANE_X 1280
# define PLANE_Y 800
# define PROJ_PLAN 1.108512516844e+03//(PLANE_X / 2) / tan(M_PI / 6)//
# define ANGLE_PACE 8.181230868723e-04 //M_PI / (3 * PLANE_X)//  //
# define TWO_PI 6.283185307180e+00 //2.0 * M_PI
# define RAY_COLOR 0xFFFF84

enum e_card{n, s, e, w, f, c};
enum e_keycode {down, right, little_right_view, half_right_view, \
	mouse_right, right_view};
typedef struct	s_vec
{
	double x;
	double y;
} t_vec;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		mini_tile_size;

}	t_image;

// typedef struct	s_vec
// {
// 	double dir_x;
// 	double dir_y;
// } t_vec;

typedef struct s_sprite
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		heigth;
	float	pos_x;
	float	pos_y;
	t_vec	pos;
}	t_sprite;


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

typedef struct s_point
{
	float	x;
	float	y;
	float	dist;
	float	angle;
	int		wall;
}	t_point;

typedef struct s_texture
{
	t_img		wall[4];
	t_img		map;
	t_sprite	cat[32];
}	t_texture;

typedef struct s_column
{
	int	column;
	int	top;
	int	bottom;
	int	size;
}	t_column;



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
	int				x;
	int				y;
	float			angle;
	t_point			raycast[1280];
	float			proj_slice_height[1280];
	t_image			image[2];
	t_texture		texture;
	int				img;
	int				keypressed[6];
	t_sprite		*cats;
}	t_cbdata;

int				create_rgb(char *line_color);
int				parse_line(t_cbdata *data, char *line);
float			calculate_distance(t_cbdata *data, t_point intersect);
bool			point_outofrange(t_cbdata *data, t_point *p);
t_point			get_h_intersect(t_cbdata *data, float angle);
t_point			get_v_intersect(t_cbdata *data, float angle);
void			init_data(t_cbdata *data);
char			**ft_mapped(int fd);
void			print_strs(char **strs);
void			parse_file(t_cbdata *data, char *av);
void			ft_free_strs(char **strs);
void			ft_free_and_close(t_cbdata *data, int fd, char *str);
void			ft_free(void **ptr);
void			cb_exit(t_cbdata *data, char *err_msg);
bool			cell_isa(char c, char *set);
bool			map_check_ok(t_cbdata *data);
int				create_rgb(char *line_color);
/* init map utils */
void			map_init(t_cbdata *data);
void			parse_map(t_cbdata *data, char *line);
void			count_map(t_cbdata *data, char *av);
int				find_one(char *str);
/* render 3d utils*/
int				get_color(t_img *img, int x, int y);
unsigned int	img_pix_read(t_cbdata *data, int text_y, int column);
/* */
void			set_move_player(t_cbdata *data, int key, int value);
void			init_game(t_cbdata *data);
void			set_hooks(t_cbdata *data);
void			change_pos_player(t_cbdata *data);
void			change_view_player(t_cbdata *data);
bool			bump_wall(t_cbdata *data, int new_x, int new_y);
void			draw_lines(t_cbdata *data);
void			redraw_mini_map(t_cbdata *data);
void			my_mlx_pixel_put(t_cbdata *data, int x, int y, int color);
void			render_3d(t_cbdata *data);
void			load_img(t_cbdata *data);
void			draw_ceillinroof(t_cbdata *data);
void			mini_tile_file(t_cbdata *data, int x, int y, int color);
void			draw_cats_center(t_cbdata *data);
#endif
