/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:00:22 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/26 14:45:58 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_BONUS_H
# define CUB_3D_BONUS_H

# define CELL_SOFT_BONUS "0NSEWM"
# define CELL_MAP_BONUS "01NSEWM"
# define CELL_THINGS "NSEWM"
# include "cub_3d.h"

/* mouse move hook bonus */
int				mouse_move_hook(int x, int y, t_cbdata *data);
int				mouse_move_hook_out(int x, int y, t_cbdata *data);
/* cats */
void			put_cat(t_cbdata *data);
/* init cat */
void			cat_init(t_cbdata *data, int x, int y);
t_list_cats		*ft_lstnew_cats(float pos_x, float pos_y);
t_list_cats		*ft_lstlast_cats(t_list_cats *lst);
void			ft_lstadd_back_cats(t_list_cats **lst, t_list_cats *new);
void			print_cats_pos(t_list_cats *cats);
void			arrange_cats_list(t_cbdata *data);
void			ft_lstclear_cats(t_list_cats **lst, void (*del)(void*));
void			print_cat_point(t_list_cats *cats);

#endif
