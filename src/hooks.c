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
	if (k == KEY_W)
		return (1);
	if (k == KEY_A)
		return (1);
	if (k == KEY_S)
		return (1);
	if (k == KEY_D)
		return (1);
	if (k == KEY_UP)
		return (1);
	if (k == KEY_LEFT)
		return (1);
	if (k == KEY_DOWN)
		return (1);
	if (k == KEY_RIGHT)
		return (1);
	return (0);
}

static void	apply_delta(int key, int *dx, int *dy)
{
	*dx = 0;
	*dy = 0;
	if (key == KEY_W || key == KEY_UP)
		*dy = -1;
	if (key == KEY_S || key == KEY_DOWN)
		*dy = 1;
	if (key == KEY_A || key == KEY_LEFT)
		*dx = -1;
	if (key == KEY_D || key == KEY_RIGHT)
		*dx = 1;
}

static void	try_move(t_game *g, int nx, int ny)
{
	char	dest;

	dest = g->map[ny][nx];
	if (dest == '1')
		return ;
	if (dest == 'E')
	{
		if (g->collect_left == 0)
		{
			g->moves++;
			ft_printf("Moves: %d\n", g->moves);
			close_win(g);
		}
		return ;
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
	int	dx;
	int	dy;

	if (key == KEY_ESC)
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
