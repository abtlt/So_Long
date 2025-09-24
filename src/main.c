/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:57:37 by abertolo          #+#    #+#             */
/*   Updated: 2025/08/28 11:57:38 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	require_args(int ac)
{
	if (ac != 2)
	{
		write(2, "Error\nusage: ./so_long <map.ber>\n", 33);
		exit(1);
	}
}

static int	check_extension(char *file)
{
	if (!ends_with(file, ".ber"))
	{
		write(2, "Error\nmap must have .ber extension\n", 35);
		return (0);
	}
	return (1);
}

static int	setup_game(char *file, t_game *g)
{
	if (!load_map(file, g))
		return (0);
	if (!check_map_rules(g))
		return (cleanup(g), 0);
	if (!flood_validate(g))
		return (cleanup(g), 0);
	if (!init_game(g))
		return (cleanup(g), 0);
	return (1);
}

static void	run_game(t_game *g)
{
	render_map(g);
	mlx_key_hook(g->win, key_press, g);
	mlx_hook(g->win, ON_DESTROY, 0, close_win, g);
	mlx_loop(g->mlx);
}

int	main(int ac, char **av)
{
	t_game	g;

	require_args(ac);
	if (!check_extension(av[1]))
		return (1);
	if (!setup_game(av[1], &g))
		return (1);
	run_game(&g);
	cleanup(&g);
	return (0);
}
