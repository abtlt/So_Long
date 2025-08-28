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

	n = ft_strlen(s);
	d = (char *)malloc(n + 1);
	if (!d)
		return (NULL);
	ft_memcpy(d, s, n);
	d[n] = '\0';
	return (d);
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*p;
	size_t	i;

	p = malloc(n * size);
	if (!p)
		return (NULL);
	for (i = 0; i < n * size; ++i)
		((unsigned char *)p)[i] = 0;
	return (p);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;
	unsigned char *d = (unsigned char *)dst;
	const unsigned char *s = (const unsigned char *)src;
	for (i = 0; i < n; ++i)
		d[i] = s[i];
	return (dst);
}