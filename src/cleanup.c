/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:59:21 by abertolo          #+#    #+#             */
/*   Updated: 2025/08/28 11:59:22 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **m)
{
	int	i;

	if (!m)
		return ;
	i = 0;
	while (m[i])
	{
		free(m[i]);
		i++;
	}
	free(m);
}

static void	destroy_images(t_game *g)
{
	if (g->floor_i.ptr)
		mlx_destroy_image(g->mlx, g->floor_i.ptr);
	if (g->wall_i.ptr)
		mlx_destroy_image(g->mlx, g->wall_i.ptr);
	if (g->player_i.ptr)
		mlx_destroy_image(g->mlx, g->player_i.ptr);
	if (g->collect_i.ptr)
		mlx_destroy_image(g->mlx, g->collect_i.ptr);
	if (g->exit_closed_i.ptr)
		mlx_destroy_image(g->mlx, g->exit_closed_i.ptr);
	if (g->exit_open_i.ptr)
		mlx_destroy_image(g->mlx, g->exit_open_i.ptr);
	g->floor_i.ptr = NULL;
	g->wall_i.ptr = NULL;
	g->player_i.ptr = NULL;
	g->collect_i.ptr = NULL;
	g->exit_closed_i.ptr = NULL;
	g->exit_open_i.ptr = NULL;
}

static void	destroy_window_and_display(t_game *g)
{
	if (g->mlx && g->win)
	{
		mlx_destroy_window(g->mlx, g->win);
		g->win = NULL;
	}
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
		g->mlx = NULL;
	}
}

void	cleanup(t_game *g)
{
	if (!g)
		return ;
	if (g->mlx && g->win)
		mlx_clear_window(g->mlx, g->win);
	if (g->mlx)
		destroy_images(g);
	destroy_window_and_display(g);
	free_map(g->map);
}
