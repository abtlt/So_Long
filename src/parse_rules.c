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

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

static void	handle_player(t_game *g, int x, int y, int *p)
{
	g->px = x;
	g->py = y;
	(*p)++;
}

static void	handle_exit(int *e)
{
	(*e)++;
}

int	valid_chars_and_locate_player(t_game *g)
{
	int	y;
	int	x;
	int	p;
	int	e;

	y = -1;
	p = 0;
	e = 0;
	while (++y < g->h)
	{
		x = -1;
		while (++x < g->w)
		{
			if (!is_valid_char(g->map[y][x]))
				return (write(2, "Error\ninvalid char in map\n", 26), 0);
			if (g->map[y][x] == 'P')
				handle_player(g, x, y, &p);
			if (g->map[y][x] == 'E')
				handle_exit(&e);
		}
	}
	if (p != 1 || e != 1 || g->collect_total < 1)
		return (write(2, "Error\nneed exactly 1 P, 1 E and >=1 C\n", 37), 0);
	return (1);
}
