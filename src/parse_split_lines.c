/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:54:05 by abertolo          #+#    #+#             */
/*   Updated: 2025/09/23 19:54:07 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_lines(const char *s)
{
	int	i;
	int	lines;

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
	return (lines);
}

static char	*alloc_line(const char *s, int start, int end)
{
	int		len;
	char	*row;

	len = end - start;
	row = (char *)ft_calloc(len + 1, 1);
	if (!row)
		return (NULL);
	ft_memcpy(row, s + start, len);
	return (row);
}

static int	fill_newline_lines(const char *s, char **tab, int *idx)
{
	int		i;
	int		start;
	char	*row;

	i = 0;
	start = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			row = alloc_line(s, start, i);
			if (!row)
				return (0);
			tab[(*idx)++] = row;
			start = i + 1;
		}
		i++;
	}
	return (start);
}

static int	fill_lines(const char *s, char **tab)
{
	int		idx;
	int		start;
	int		i;
	char	*row;

	idx = 0;
	start = fill_newline_lines(s, tab, &idx);
	i = 0;
	while (s[i])
		i++;
	if (i > start)
	{
		row = alloc_line(s, start, i);
		if (!row)
			return (0);
		tab[idx++] = row;
	}
	tab[idx] = NULL;
	return (1);
}

char	**split_lines(const char *s)
{
	char	**tab;
	int		lines;

	lines = count_lines(s);
	tab = (char **)ft_calloc(lines + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	if (!fill_lines(s, tab))
	{
		free_map(tab);
		return (NULL);
	}
	return (tab);
}
