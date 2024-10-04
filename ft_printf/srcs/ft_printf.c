/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:46:38 by pavicent          #+#    #+#             */
/*   Updated: 2024/03/21 10:46:41 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex_pointer(unsigned long n)
{
	int	result;
	int	hex;

	if (n == 0)
	{
		result = ft_putstr("(nil)");
		return (result);
	}
	result = ft_putstr("0x");
	if (result == -1)
		return (-1);
	hex = ft_putnbr_base(n, "0123456789abcdef", 0);
	if (hex == -1)
		return (-1);
	return (result + hex);
}

int	ft_check_format(char format, va_list args)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_hex_pointer(va_arg(args, unsigned long)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbrpr(va_arg(args, int)));
	else if (format == 'u')
		return (ft_putunbr(va_arg(args, unsigned int)));
	else if (format == 'x')
		return (ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef",
				0));
	else if (format == 'X')
		return (ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF",
				0));
	else if (format == '%')
		return (ft_putchar('%'));
	return (-1);
}

int	ft_format(const char *format, int *i, va_list args)
{
	int	count;

	count = 0;
	if (*(format + *i) == '%' && *(format + *i + 1) != '\0')
	{
		(*i)++;
		count = ft_check_format(*(format + *i), args);
		if (count == -1)
			return (-1);
	}
	else if (*(format + *i) != '%')
	{
		count = ft_putchar(*(format + *i));
		if (count == -1)
			return (-1);
	}
	(*i)++;
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;
	int		result;

	va_start(args, format);
	count = 0;
	i = 0;
	result = 0;
	if (format)
	{
		while (*(format + i))
		{
			result = ft_format(format, &i, args);
			if (result == -1)
			{
				va_end(args);
				return (-1);
			}
			count += result;
		}
	}
	va_end(args);
	return (count);
}
