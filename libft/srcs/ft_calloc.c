/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:23:05 by pavicent          #+#    #+#             */
/*   Updated: 2024/02/28 09:29:05 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tab;
	size_t			i;

	i = 0;
	tab = (unsigned char *)malloc(size * count);
	if (!tab)
		return (NULL);
	while (i < count * size)
		tab[i++] = '\0';
	return (tab);
}
