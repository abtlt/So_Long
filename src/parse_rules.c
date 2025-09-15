/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rules..c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:40:52 by abertolo          #+#    #+#             */
/*   Updated: 2025/09/02 16:40:53 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_rectangular(t_game *g)
{
	int		y;
	size_t	w;

	y = 0;
	w = ft_strlen(g->map[0]);
	while (g->map[y])
	{
		if (ft_strlen(g->map[y]) != w)
			return (0);
		y++;
	}
	return (1);
}

static int	borders_are_walls(t_game *g)
{
	int	x;
	int	y;

	x = 0;
	while (x < g->w)
	{
		if (g->map[0][x] != '1')
			return (0);
		if (g->map[g->h - 1][x] != '1')
			return (0);
		x++;
	}
	y = 0;
	while (y < g->h)
	{
		if (g->map[y][0] != '1')
			return (0);
		if (g->map[y][g->w - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}

static int	valid_chars_and_locate_player(t_game *g)
{
	int	y;
	int	x;
	int	p;
	int	e;

	y = 0;
	p = 0;
	e = 0;
	while (y < g->h)
	{
		x = 0;
		while (x < g->w)
		{
			if (g->map[y][x] != '0' && g->map[y][x] != '1'
				&& g->map[y][x] != 'C' && g->map[y][x] != 'E'
				&& g->map[y][x] != 'P')
				return (write(2, "Error\ninvalid char in map\n", 26), 0);
			if (g->map[y][x] == 'P')
			{
				g->px = x;
				g->py = y;
				p++;
			}
			if (g->map[y][x] == 'E')
				e++;
			x++;
		}
		y++;
	}
	if (p != 1 || e != 1 || g->collect_total < 1)
		return (write(2, "Error\nneed exactly 1 P, 1 E and >=1 C\n", 37), 0);
	return (1);
}

int	check_map_rules(t_game *g)
{
	if (!is_rectangular(g))
		return (write(2, "Error\nmap must be rectangular\n", 29), 0);
	if (!borders_are_walls(g))
		return (write(2, "Error\nmap must be closed by walls\n", 31), 0);
	if (!valid_chars_and_locate_player(g))
		return (0);
	return (1);
}
