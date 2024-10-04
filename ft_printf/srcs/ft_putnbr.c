/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:23:22 by pavicent          #+#    #+#             */
/*   Updated: 2024/04/02 11:23:43 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrpr(int n)
{
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	else
	{
		if (n < 0)
		{
			if (ft_putchar('-') == -1)
				return (-1);
			n = -n;
			return (ft_putnbrpr(n) + 1);
		}
		return (ft_putunbr(n));
	}
}
