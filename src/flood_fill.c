/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:58:21 by abertolo          #+#    #+#             */
/*   Updated: 2025/08/28 11:58:22 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**dup_map(t_game *g)
{
	char	**cp;
	int		y;

	cp = (char **)ft_calloc(g->h + 1, sizeof(char *));
	if (!cp)
		return (NULL);
	for (y = 0; y < g->h; ++y)
	{
		cp[y] = ft_strdup(g->map[y]);
		if (!cp[y])
			return (free_map(cp), (char **)0);
	}
	return (cp);
}

static void	ff(char **m, int h, int w, int y, int x)
{
	if (y < 0 || x < 0 || y >= h || x >= w)
		return ;
	if (m[y][x] == '1' || m[y][x] == 'V')
		return ;
	m[y][x] = 'V';
	ff(m, h, w, y + 1, x);
	ff(m, h, w, y - 1, x);
	ff(m, h, w, y, x + 1);
	ff(m, h, w, y, x - 1);
}

int	flood_validate(t_game *g)
{
	char	**m;
	int		c_ok;
	int		e_ok;

	int y, x;
	c_ok = 0;
	e_ok = 0;
	m = dup_map(g);
	if (!m)
		return (write(2, "Error\nalloc\n", 12), 0);
	ff(m, g->h, g->w, g->py, g->px);
	for (y = 0; y < g->h; ++y)
	{
		for (x = 0; x < g->w; ++x)
		{
			if (g->map[y][x] == 'C' && m[y][x] == 'V')
				c_ok++;
			if (g->map[y][x] == 'E' && ((y + 1 < g->h && m[y + 1][x] == 'V')
					|| (y > 0 && m[y - 1][x] == 'V') || (x + 1 < g->w && m[y][x
						+ 1] == 'V') || (x > 0 && m[y][x - 1] == 'V')))
				e_ok = 1;
		}
	}
	free_map(m);
	if (c_ok != g->collect_total || !e_ok)
		return (write(2, "Error\nno valid path to collect all and reach exit\n",
				47), 0);
	return (1);
}
