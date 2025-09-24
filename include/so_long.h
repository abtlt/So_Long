/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:13:15 by abertolo          #+#    #+#             */
/*   Updated: 2025/09/02 16:13:17 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE 64
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define ON_DESTROY 17

typedef struct s_img
{
	void	*ptr;
	int		w;
	int		h;
}			t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		w;
	int		h;
	int		px;
	int		py;
	int		moves;
	int		collect_total;
	int		collect_left;
	t_img	floor_i;
	t_img	wall_i;
	t_img	player_i;
	t_img	collect_i;
	t_img	exit_closed_i;
	t_img	exit_open_i;
}			t_game;

int			load_map(const char *path, t_game *g);
int			check_map_rules(t_game *g);
int			flood_validate(t_game *g);
int			init_game(t_game *g);
void		load_textures(t_game *g);
void		render_map(t_game *g);
int			key_press(int key, t_game *g);
int			close_win(t_game *g);
void		fatal(const char *msg, t_game *g);
void		cleanup(t_game *g);
void		free_map(char **map);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
void		*ft_calloc(size_t n, size_t size);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		**split_lines(const char *s);
char		*read_all(int fd);
int			ends_with(const char *s, const char *suf);
int			ft_printf(const char *fmt, ...);
int			valid_chars_and_locate_player(t_game *g);

#endif
