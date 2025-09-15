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

int	main(int ac, char **av)
{
	t_game	g;

	require_args(ac);
	if (!ends_with(av[1], ".ber"))
	{
		write(2, "Error\nmap must have .ber extension\n", 35);
		return (1);
	}
	if (!load_map(av[1], &g))
		return (1);
	if (!check_map_rules(&g))
	{
		cleanup(&g);
		return (1);
	}
	if (!flood_validate(&g))
	{
		cleanup(&g);
		return (1);
	}
	if (!init_game(&g))
	{
		cleanup(&g);
		return (1);
	}
	render_map(&g);
	mlx_key_hook(g.win, key_press, &g);
	mlx_hook(g.win, ON_DESTROY, 0, close_win, &g);
	mlx_loop(g.mlx);
	cleanup(&g);
	return (0);
}
