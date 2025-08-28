/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:58:58 by abertolo          #+#    #+#             */
/*   Updated: 2025/08/28 11:58:59 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_move_key(int k)
{
	return (k == KEY_W || k == KEY_A || k == KEY_S || k == KEY_D
		|| k == KEY_W_MAC || k == KEY_A_MAC || k == KEY_S_MAC || k == KEY_D_MAC
		|| k == KEY_UP || k == KEY_LEFT || k == KEY_DOWN || k == KEY_RIGHT);
}

static void	apply_delta(int key, int *dx, int *dy)
{
	*dx = 0;
	*dy = 0;
	if (key == KEY_W || key == KEY_W_MAC || key == KEY_UP)
		*dy = -1;
	if (key == KEY_S || key == KEY_S_MAC || key == KEY_DOWN)
		*dy = 1;
	if (key == KEY_A || key == KEY_A_MAC || key == KEY_LEFT)
		*dx = -1;
	if (key == KEY_D || key == KEY_D_MAC || key == KEY_RIGHT)
		*dx = 1;
}

static void	try_move(t_game *g, int nx, int ny)
{
	char	dest;

	dest = g->map[ny][nx];
	if (dest == '1')
		return ; /* wall */
	if (dest == 'E')
	{
		if (g->collect_left == 0)
		{
			g->moves++;
			ft_printf("Moves: %d\n", g->moves);
			close_win(g);
		}
		return ; /* block exit until all C */
	}
	if (dest == 'C')
	{
		g->collect_left--;
		g->map[ny][nx] = '0';
	}
	g->px = nx;
	g->py = ny;
	g->moves++;
	ft_printf("Moves: %d\n", g->moves);
	render_map(g);
}

int	key_press(int key, t_game *g)
{
	int dx, dy;
	if (key == KEY_ESC || key == KEY_ESC_MAC)
		return (close_win(g));
	if (is_move_key(key))
	{
		apply_delta(key, &dx, &dy);
		try_move(g, g->px + dx, g->py + dy);
	}
	return (0);
}

int	close_win(t_game *g)
{
	cleanup(g);
	exit(0);
	return (0);
}
