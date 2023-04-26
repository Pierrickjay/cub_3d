/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:00:22 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/26 13:54:53 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_BONUS_H
# define CUB_3D_BONUS_H

# define CELL_SOFT_BONUS "0NSEWM"
# define CELL_MAP_BONUS "01NSEWM"
# define CELL_THINGS "NSEWM"

typedef struct s_app_cat
{
	float	x;
	float	y;
	float	reduct;
	int		offset_x;
	int		offset_y;
}	t_app_cat;

/* mouse move hook bonus */
int		mouse_move_hook(int x, int y, t_cbdata *data);
int		mouse_move_hook_out(int x, int y, t_cbdata *data);
/* cats */
void	put_cat(t_cbdata *data);
/* draw slice */
void	draw_slice(t_cbdata *data, int current_x, t_app_cat kitty);
/* init cat */
void	cat_init(t_cbdata *data, int x, int y);
#endif
