/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:50:07 by abertolo          #+#    #+#             */
/*   Updated: 2025/09/23 19:50:09 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*init_buffer(size_t cap)
{
	char	*out;

	out = (char *)ft_calloc(cap + 1, 1);
	if (!out)
		return (NULL);
	return (out);
}

static int	expand_buffer(char **out, size_t *cap, size_t need, size_t sz)
{
	char	*tmp;
	size_t	newcap;

	newcap = *cap * 2;
	if (newcap < need)
		newcap = need;
	while (newcap < need)
		newcap *= 2;
	tmp = (char *)ft_calloc(newcap, 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *out, sz);
	free(*out);
	*out = tmp;
	*cap = newcap;
	return (1);
}

static void	copy_data(char *out, char *buf, size_t n, size_t sz)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		out[sz + i] = buf[i];
		i++;
	}
	out[sz + n] = '\0';
}

static int	read_loop(int fd, char **out, size_t *sz, size_t *cap)
{
	char	buf[1024];
	ssize_t	n;

	n = read(fd, buf, sizeof(buf));
	while (n > 0)
	{
		if (*sz + (size_t)n + 1 > *cap)
		{
			if (!expand_buffer(out, cap, *sz + (size_t)n + 1, *sz))
				return (0);
		}
		copy_data(*out, buf, (size_t)n, *sz);
		*sz += (size_t)n;
		n = read(fd, buf, sizeof(buf));
	}
	if (n < 0)
		return (0);
	return (1);
}

char	*read_all(int fd)
{
	size_t	cap;
	size_t	sz;
	char	*out;

	cap = 1024;
	out = init_buffer(cap);
	if (!out)
		return (NULL);
	sz = 0;
	if (!read_loop(fd, &out, &sz, &cap))
	{
		free(out);
		return (NULL);
	}
	return (out);
}
