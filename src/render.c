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

static void	render_tile(t_game *g, char c, int x, int y)
{
	put(g, &g->floor_i, x, y);
	if (c == '1')
		put(g, &g->wall_i, x, y);
	else if (c == 'C')
		put(g, &g->collect_i, x, y);
	else if (c == 'E')
	{
		if (g->collect_left > 0)
			put(g, &g->exit_closed_i, x, y);
		else
			put(g, &g->exit_open_i, x, y);
	}
}

void	render_map(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->h)
	{
		x = 0;
		while (x < g->w)
		{
			render_tile(g, g->map[y][x], x, y);
			x++;
		}
		y++;
	}
	put(g, &g->player_i, g->px, g->py);
}
