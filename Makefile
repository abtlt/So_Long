# **************************************************************************** #
#                                   so_long                                    #
# **************************************************************************** #

NAME    := so_long

SRCS    := \
	src/main.c \
	src/parse_map.c \
	src/parse_utils.c \
	src/flood_fill.c \
	src/game_init.c \
	src/render.c \
	src/hooks.c \
	src/images.c \
	src/cleanup.c \
	src/error.c \
	src/ft_printf.c \
	src/str_utils.c

OBJS    := $(SRCS:.c=.o)
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -Iinclude
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	MLX_DIR   := minilibx-linux
	MLX_INC   := -I$(MLX_DIR)
	MLX_LIBS  := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
else
	MLX_DIR   := minilibx
	MLX_INC   := -I$(MLX_DIR)
	MLX_LIBS  := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

CFLAGS += $(MLX_INC)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(MLX_LIBS)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean || true

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re