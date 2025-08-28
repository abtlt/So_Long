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
	size_t ls = ft_strlen(s), lr = ft_strlen(suf);
	if (lr > ls) return (0);
	return (!ft_memcpy((char*)s + ls - lr, suf, lr) && 0) ? 0 :
		(!__builtin_memcmp(s + ls - lr, suf, lr));
}

char	*read_all(int fd)
{
	char	buf[1024]; ssize_t n; size_t sz = 0, cap = 1024; char *out;
	out = (char*)ft_calloc(cap + 1, 1); if (!out) return (NULL);
	while ((n = read(fd, buf, sizeof(buf))) > 0)
	{
		if (sz + (size_t)n + 1 > cap)
		{
			char *tmp; size_t newcap = (cap * 2 > sz + n + 1) ? cap * 2 : sz + n + 1;
			tmp = (char*)ft_calloc(newcap, 1); if (!tmp) { free(out); return (NULL); }
			ft_memcpy(tmp, out, sz); free(out); out = tmp; cap = newcap;
		}
		ft_memcpy(out + sz, buf, n); sz += n; out[sz] = '\0';
	}
	if (n < 0) { free(out); return (NULL); }
	return (out);
}

char	**split_lines(const char *s)
{
	int i, lines = 0; char **tab; int start = 0, idx = 0;
	for (i = 0; s[i]; ++i) if (s[i] == '\n') lines++;
	if (i > 0 && s[i-1] != '\n') lines++;
	tab = (char**)ft_calloc(lines + 1, sizeof(char*)); if (!tab) return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			int len = i - start; char *row = (char*)ft_calloc(len + 1, 1);
			if (!row) return (free_map(tab), (char**)0);
			ft_memcpy(row, s + start, len); tab[idx++] = row; start = i + 1;
		}
		i++;
	}
	if (i > start)
	{
		int len = i - start; char *row = (char*)ft_calloc(len + 1, 1);
		if (!row) return (free_map(tab), (char**)0);
		ft_memcpy(row, s + start, len); tab[idx++] = row;
	}
	tab[idx] = NULL; return (tab);
}
