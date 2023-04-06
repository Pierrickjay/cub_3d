/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_strs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:17:15 by pjay              #+#    #+#             */
/*   Updated: 2023/04/06 11:17:18 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	print_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		printf("%s", strs[i]);
		i++;
	}
}
