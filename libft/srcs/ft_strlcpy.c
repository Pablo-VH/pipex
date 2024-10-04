/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:39:12 by pavicent          #+#    #+#             */
/*   Updated: 2024/01/29 12:27:43 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(src);
	j = 0;
	if (dstsize == 0)
		return (i);
	if (i + 1 <= dstsize)
	{
		while (src[j] != '\0')
		{
			dst[j] = src[j];
			j++;
		}
	}
	if (i + 1 > dstsize)
	{
		while (j < dstsize - 1)
		{
			dst[j] = src[j];
			j++;
		}
	}
	dst[j] = '\0';
	return (i);
}
