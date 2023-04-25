/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:51:11 by obouhlel          #+#    #+#             */
/*   Updated: 2023/04/25 16:00:21 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

//strlcpy it's for copy the dest and the source, and we return the lenth
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (size > len)
		size = len + 1;
	else if (size == 0)
		return (len);
	while (i < size - 1)
	{
		DP
		printf("i = %zu\n", i);
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (len);
}
