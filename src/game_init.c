/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:58:32 by abertolo          #+#    #+#             */
/*   Updated: 2025/08/28 11:58:34 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	find_player(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->h)
	{
		x = 0;
		while (x < g->w)
		{
			if (g->map[y][x] == 'P')
			{
				g->px = x;
				g->py = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	init_game(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		return (write(2, "Error\nmlx_init failed\n", 21), 0);
	g->win = mlx_new_window(g->mlx, g->w * TILE, g->h * TILE, "so_long");
	if (!g->win)
		return (write(2, "Error\nwindow failed\n", 21), 0);
	find_player(g);
	load_textures(g);
	return (1);
}
