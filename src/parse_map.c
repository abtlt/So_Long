/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:14:54 by abertolo          #+#    #+#             */
/*   Updated: 2025/09/02 16:14:55 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_char(char **m, char c)
{
	int	y;
	int	x;
	int	cnt;

	y = 0;
	cnt = 0;
	while (m[y])
	{
		x = 0;
		while (m[y][x])
		{
			if (m[y][x] == c)
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}

int	load_map(const char *path, t_game *g)
{
	char	*buf;
	int		fd;
	int		i;

	g->map = NULL;
	g->mlx = NULL;
	g->win = NULL;
	g->moves = 0;
	g->collect_total = 0;
	g->collect_left = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error\nfailed to open map\n", 25), 0);
	buf = read_all(fd);
	close(fd);
	if (!buf)
		return (write(2, "Error\nfailed to read map\n", 25), 0);
	g->map = split_lines(buf);
	free(buf);
	if (!g->map || !g->map[0])
		return (write(2, "Error\nempty or invalid map\n", 26), 0);
	g->h = 0;
	while (g->map[g->h])
		g->h++;
	g->w = ft_strlen(g->map[0]);
	g->collect_total = count_char(g->map, 'C');
	g->collect_left = g->collect_total;
	i = 0;
	while (i < g->h)
		i++;
	return (1);
}
