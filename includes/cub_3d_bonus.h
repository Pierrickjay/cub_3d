/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:00:22 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/25 14:55:22 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_BONUS_H
# define CUB_3D_BONUS_H

# define CELL_SOFT_BONUS "0NSEWM"
# define CELL_MAP_BONUS "01NSEWM"
# define CELL_THINGS "NSEWM"

# define DP printf("%s %d\n", __FILE__, __LINE__);


/* mouse move hook bonus */
int	mouse_move_hook(int x, int y, t_cbdata *data);
int	mouse_move_hook_out(int x, int y, t_cbdata *data);
/* cats */
void	put_cat(t_cbdata *data);
/* init cat */
void	cat_init(t_cbdata *data, int x, int y);
#endif
