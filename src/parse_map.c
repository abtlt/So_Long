#include "so_long.h"

static int	count_char(char **m, char c)
{
	int y, x, cnt = 0;
	for (y = 0; m[y]; ++y)
		for (x = 0; m[y][x]; ++x)
			if (m[y][x] == c)
				cnt++;
	return (cnt);
}

int	load_map(const char *path, t_game *g)
{
	char	*buf;
	int		fd;

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
	return (1);
}

static int	is_rectangular(t_game *g)
{
	int		y;
	size_t	w;

	w = ft_strlen(g->map[0]);
	for (y = 0; g->map[y]; ++y)
		if (ft_strlen(g->map[y]) != w)
			return (0);
	return (1);
}

static int	borders_are_walls(t_game *g)
{
	int x, y;
	for (x = 0; x < g->w; ++x)
		if (g->map[0][x] != '1' || g->map[g->h - 1][x] != '1')
			return (0);
	for (y = 0; y < g->h; ++y)
		if (g->map[y][0] != '1' || g->map[y][g->w - 1] != '1')
			return (0);
	return (1);
}

static int	valid_chars_and_locate_player(t_game *g)
{
	char	c;

	int y, x, p = 0, e = 0;
	for (y = 0; y < g->h; ++y)
	{
		for (x = 0; x < g->w; ++x)
		{
			c = g->map[y][x];
			if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
				return (write(2, "Error\ninvalid char in map\n", 26), 0);
			if (c == 'P')
			{
				g->px = x;
				g->py = y;
				p++;
			}
			if (c == 'E')
				e++;
		}
	}
	if (p != 1 || e != 1 || g->collect_total < 1)
		return (write(2, "Error\nneed exactly 1 P, 1 E and >=1 C\n", 37), 0);
	return (1);
}

int	check_map_rules(t_game *g)
{
	if (!is_rectangular(g))
		return (write(2, "Error\nmap must be rectangular\n", 29), 0);
	if (!borders_are_walls(g))
		return (write(2, "Error\nmap must be closed by walls\n", 31), 0);
	if (!valid_chars_and_locate_player(g))
		return (0);
	return (1);
}
