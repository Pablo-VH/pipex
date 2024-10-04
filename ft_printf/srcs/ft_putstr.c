/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:02:01 by pavicent          #+#    #+#             */
/*   Updated: 2024/04/04 12:02:04 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	if (s == NULL)
		return (ft_putstr("(null)"));
	while (s[count] != '\0')
	{
		if (ft_putchar(s[count]) == -1)
			return (-1);
		count++;
	}
	return (count);
}
