NAME = cub3D

SRC_FILES = raycasting/utils.c \
            raycasting/raycasting.c \
            raycasting/player.c

OBJS = $(SRC_FILES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

# --- Linux MLX ---
MLX_DIR = minilibx-linux
MLX_FLAGS = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm

# --- Libft ---
LIBFT = ./libft/libft.a

# --- Include paths ---
INC = -I . -I ./raycasting -I ./libft -I ./$(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INC) $(OBJS) $(MLX_FLAGS) -L ./libft -lft -o $(NAME)

$(LIBFT):
	make -C ./libft all

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	make -C ./libft clean
	rm -f $(OBJS)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
