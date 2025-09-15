/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:19:17 by abertolo          #+#    #+#             */
/*   Updated: 2025/08/28 14:19:19 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ends_with(const char *s, const char *suf)
{
	size_t	ls;
	size_t	lr;
	size_t	i;

	ls = ft_strlen(s);
	lr = ft_strlen(suf);
	if (lr > ls)
		return (0);
	i = 0;
	while (i < lr && s[ls - lr + i] == suf[i])
		i++;
	if (i == lr)
		return (1);
	return (0);
}

char	*read_all(int fd)
{
	char	buf[1024];
	ssize_t	n;
	size_t	sz;
	size_t	cap;
	char	*out;
	char	*tmp;
	size_t	newcap;
	size_t	i;

	cap = 1024;
	out = (char *)ft_calloc(cap + 1, 1);
	if (!out)
		return (NULL);
	sz = 0;
	n = read(fd, buf, sizeof(buf));
	while (n > 0)
	{
		if (sz + (size_t)n + 1 > cap)
		{
			newcap = cap * 2;
			if (newcap < sz + (size_t)n + 1)
				newcap = sz + (size_t)n + 1;
			while (newcap < sz + (size_t)n + 1)
				newcap = newcap * 2;
			tmp = (char *)ft_calloc(newcap, 1);
			if (!tmp)
			{
				free(out);
				return (NULL);
			}
			ft_memcpy(tmp, out, sz);
			free(out);
			out = tmp;
			cap = newcap;
		}
		i = 0;
		while (i < (size_t)n)
		{
			out[sz + i] = buf[i];
			i++;
		}
		sz += (size_t)n;
		out[sz] = '\0';
		n = read(fd, buf, sizeof(buf));
	}
	if (n < 0)
	{
		free(out);
		return (NULL);
	}
	return (out);
}

char	**split_lines(const char *s)
{
	int		i;
	int		lines;
	char	**tab;
	int		start;
	int		idx;
	int		len;
	char	*row;

	i = 0;
	lines = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			lines++;
		i++;
	}
	if (i > 0 && s[i - 1] != '\n')
		lines++;
	tab = (char **)ft_calloc(lines + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	start = 0;
	idx = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			len = i - start;
			row = (char *)ft_calloc(len + 1, 1);
			if (!row)
			{
				free_map(tab);
				return (NULL);
			}
			ft_memcpy(row, s + start, len);
			tab[idx++] = row;
			start = i + 1;
		}
		i++;
	}
	if (i > start)
	{
		len = i - start;
		row = (char *)ft_calloc(len + 1, 1);
		if (!row)
		{
			free_map(tab);
			return (NULL);
		}
		ft_memcpy(row, s + start, len);
		tab[idx++] = row;
	}
	tab[idx] = NULL;
	return (tab);
}
