/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:25:06 by pavicent          #+#    #+#             */
/*   Updated: 2024/04/02 11:25:13 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned long n, char *base, int result)
{
	unsigned long	len_base;

	len_base = ft_strlenpr(base);
	if (n < len_base)
	{
		if (ft_putchar(base[n]) == -1)
			return (-1);
		return (result + 1);
	}
	else
	{
		result = ft_putnbr_base(n / len_base, base, result);
		if (result == -1)
			return (-1);
		if (ft_putchar(base[n % len_base]) == -1)
			return (-1);
		return (result + 1);
	}
}
