/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:00:02 by abertolo          #+#    #+#             */
/*   Updated: 2025/08/28 12:00:03 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	n;
	char	*d;
	size_t	i;

	n = ft_strlen(s);
	d = (char *)malloc(n + 1);
	if (!d)
		return (NULL);
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	d[n] = '\0';
	return (d);
}

void	*ft_calloc(size_t n, size_t size)
{
	void			*p;
	size_t			i;
	unsigned char	*b;
	size_t			total;

	if (size != 0 && n > (size_t)-1 / size)
		return (NULL);
	p = malloc(n * size);
	if (!p)
		return (NULL);
	b = (unsigned char *)p;
	total = n * size;
	i = 0;
	while (i < total)
	{
		b[i] = 0;
		i++;
	}
	return (p);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
