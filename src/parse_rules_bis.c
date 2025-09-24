/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rules_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:57:13 by abertolo          #+#    #+#             */
/*   Updated: 2025/09/22 12:57:15 by abertolo         ###   ########.fr       */
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
		if (g->map[0][x] != '1' || g->map[g->h - 1][x] != '1')
			return (0);
		x++;
	}
	y = 0;
	while (y < g->h)
	{
		if (g->map[y][0] != '1' || g->map[y][g->w - 1] != '1')
			return (0);
		y++;
	}
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
