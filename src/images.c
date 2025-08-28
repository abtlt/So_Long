/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:59:08 by abertolo          #+#    #+#             */
/*   Updated: 2025/08/28 11:59:09 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_one(t_game *g, t_img *im, const char *path)
{
	im->ptr = mlx_xpm_file_to_image(g->mlx, (char *)path, &im->w, &im->h);
	if (!im->ptr)
		fatal("failed to load xpm", g);
}

void	load_textures(t_game *g)
{
	load_one(g, &g->floor_i, "assets/floor.xpm");
	load_one(g, &g->wall_i, "assets/wall.xpm");
	load_one(g, &g->player_i, "assets/player.xpm");
	load_one(g, &g->collect_i, "assets/collect.xpm");
	load_one(g, &g->exit_closed_i, "assets/exit_closed.xpm");
	load_one(g, &g->exit_open_i, "assets/exit_open.xpm");
}
