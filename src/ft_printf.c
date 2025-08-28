/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:59:50 by abertolo          #+#    #+#             */
/*   Updated: 2025/08/28 11:59:51 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdarg.h>

static int	putnbr_rec(long n)
{
	char	c;
	int		cnt;

	cnt = 0;
	if (n < 0)
	{
		cnt += write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		cnt += putnbr_rec(n / 10);
	c = '0' + (n % 10);
	cnt += write(1, &c, 1);
	return (cnt);
}

int	ft_printf(const char *fmt, ...)
{
	va_list ap;
	int i = 0;
	int out = 0;
	va_start(ap, fmt);
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1])
		{
			if (fmt[i + 1] == 'd' || fmt[i + 1] == 'i')
				out += putnbr_rec(va_arg(ap, int)), i += 2;
			else if (fmt[i + 1] == 's')
			{
				char *s = va_arg(ap, char *);
				if (!s)
					s = "(null)";
				out += write(1, s, ft_strlen(s));
				i += 2;
			}
			else if (fmt[i + 1] == '%')
				out += write(1, "%", 1), i += 2;
			else
				out += write(1, &fmt[i++], 1);
		}
		else
			out += write(1, &fmt[i++], 1);
	}
	va_end(ap);
	return (out);
}