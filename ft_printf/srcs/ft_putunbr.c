/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:47:09 by pavicent          #+#    #+#             */
/*   Updated: 2024/04/04 11:48:06 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr(unsigned int n)
{
	int	i;

	i = 0;
	if (n > 9)
	{
		i = ft_putunbr(n / 10);
		if (i == -1)
			return (-1);
	}
	if (ft_putchar(n % 10 + '0') == -1)
		return (-1);
	i++;
	return (i);
}
