/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:58:44 by abertolo          #+#    #+#             */
/*   Updated: 2025/08/28 11:58:45 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put(t_game *g, t_img *i, int x, int y)
{
	mlx_put_image_to_window(g->mlx, g->win, i->ptr, x * TILE, y * TILE);
}

void	render_map(t_game *g)
{
	char	c;

	int y, x;
	for (y = 0; y < g->h; ++y)
	{
		for (x = 0; x < g->w; ++x)
		{
			c = g->map[y][x];
			put(g, &g->floor_i, x, y);
			if (c == '1')
				put(g, &g->wall_i, x, y);
			else if (c == 'C')
				put(g, &g->collect_i, x, y);
			else if (c == 'E')
				put(g, g->collect_left ? &g->exit_closed_i : &g->exit_open_i, x,
					y);
		}
	}
	put(g, &g->player_i, g->px, g->py);
}
