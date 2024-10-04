/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:29:38 by pavicent          #+#    #+#             */
/*   Updated: 2024/04/05 11:29:42 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stddef.h>

int	ft_printf(const char *format, ...);
int	ft_putchar(int c);
int	ft_putstr(char *s);
int	ft_putnbrpr(int n);
int	ft_putunbr(unsigned int n);
int	ft_putnbr_base(unsigned long n, char *base, int result);
int	ft_hex_pointer(unsigned long n);
int	ft_check_format(char format, va_list args);
int	ft_format(const char *format, int *i, va_list args);
int	ft_strlenpr(const char *s);

#endif
