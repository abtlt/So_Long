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
	for (i = 0; m[i]; ++i)
		free(m[i]);
	free(m);
}

static void	destroy_img(void *mlx, t_img *im)
{
	if (im->ptr)
		mlx_destroy_image(mlx, im->ptr);
	im->ptr = NULL;
}

void	cleanup(t_game *g)
{
	if (!g)
		return ;
	if (g->mlx && g->win)
		mlx_clear_window(g->mlx, g->win);
	if (g->mlx)
	{
		destroy_img(g->mlx, &g->floor_i);
		destroy_img(g->mlx, &g->wall_i);
		destroy_img(g->mlx, &g->player_i);
		destroy_img(g->mlx, &g->collect_i);
		destroy_img(g->mlx, &g->exit_closed_i);
		destroy_img(g->mlx, &g->exit_open_i);
	}
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
	free_map(g->map);
}