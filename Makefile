# **************************************************************************** #
#                                   so_long                                    #
# **************************************************************************** #

NAME := so_long
MLX_DIR := minilibx-linux
MLX_REPO := https://github.com/42paris/minilibx-linux.git

SRCS := \
	src/main.c \
	src/parse_map.c \
	src/parse_rules.c \
	src/flood_fill.c \
	src/game_init.c \
	src/render.c \
	src/hooks.c \
	src/images.c \
	src/cleanup.c \
	src/error.c \
	src/ft_printf.c \
	src/parse_utils.c \
	src/str_utils.c \
	src/parse_rules_bis.c \
	src/parse_read_all.c \
	src/parse_split_lines.c

OBJS := $(SRCS:.c=.o)
CC := cc
CFLAGS := -Wall -Wextra -Werror -Iinclude -I$(MLX_DIR)
MLX_LIBS := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)

$(MLX_DIR)/libmlx.a: | $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

$(OBJS): | $(MLX_DIR)/libmlx.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_LIBS)

clean:
	$(RM) $(OBJS)
	-$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re
