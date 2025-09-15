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
	y = 0;
	while (y < g->h)
	{
		cp[y] = ft_strdup(g->map[y]);
		if (!cp[y])
		{
			free_map(cp);
			return (NULL);
		}
		y++;
	}
	return (cp);
}

static void	ff(t_game *g, char **m, int y, int x)
{
	if (y < 0 || x < 0 || y >= g->h || x >= g->w)
		return ;
	if (m[y][x] == '1' || m[y][x] == 'V')
		return ;
	m[y][x] = 'V';
	ff(g, m, y + 1, x);
	ff(g, m, y - 1, x);
	ff(g, m, y, x + 1);
	ff(g, m, y, x - 1);
}

int	flood_validate(t_game *g)
{
	char	**m;
	int		y;
	int		x;
	int		c_ok;
	int		e_ok;

	m = dup_map(g);
	if (!m)
		return (write(2, "Error\nalloc\n", 12), 0);
	ff(g, m, g->py, g->px);
	y = 0;
	c_ok = 0;
	e_ok = 0;
	while (y < g->h)
	{
		x = 0;
		while (x < g->w)
		{
			if (g->map[y][x] == 'C' && m[y][x] == 'V')
				c_ok++;
			if (g->map[y][x] == 'E')
			{
				if (y + 1 < g->h && m[y + 1][x] == 'V')
					e_ok = 1;
				if (y > 0 && m[y - 1][x] == 'V')
					e_ok = 1;
				if (x + 1 < g->w && m[y][x + 1] == 'V')
					e_ok = 1;
				if (x > 0 && m[y][x - 1] == 'V')
					e_ok = 1;
			}
			x++;
		}
		y++;
	}
	free_map(m);
	if (c_ok != g->collect_total || !e_ok)
		return (write(2, "Error\nno valid path to collect all and reach exit\n",
				47), 0);
	return (1);
}
