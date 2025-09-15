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

static int	putstr_safe(const char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}

static int	handle_conv(const char *fmt, int *i, va_list *ap)
{
	int	out;

	out = 0;
	if (fmt[*i + 1] == 'd' || fmt[*i + 1] == 'i')
	{
		out += putnbr_rec(va_arg(*ap, int));
		*i += 2;
		return (out);
	}
	if (fmt[*i + 1] == 's')
	{
		out += putstr_safe(va_arg(*ap, char *));
		*i += 2;
		return (out);
	}
	if (fmt[*i + 1] == '%')
	{
		out += write(1, "%", 1);
		*i += 2;
		return (out);
	}
	out += write(1, &fmt[*i], 1);
	*i += 1;
	return (out);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		i;
	int		out;

	va_start(ap, fmt);
	i = 0;
	out = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1])
			out += handle_conv(fmt, &i, &ap);
		else
		{
			out += write(1, &fmt[i], 1);
			i++;
		}
	}
	va_end(ap);
	return (out);
}
