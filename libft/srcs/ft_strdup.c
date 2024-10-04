/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:23:03 by pavicent          #+#    #+#             */
/*   Updated: 2024/02/21 17:15:28 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*duplicate;

	len = ft_strlen((char *)s1) + 1;
	duplicate = (char *)malloc(len);
	if (duplicate == NULL)
		return (NULL);
	ft_strlcpy(duplicate, s1, len);
	return ((char *)duplicate);
}
