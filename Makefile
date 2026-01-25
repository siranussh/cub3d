NAME = cub3D

SRC_RAY = raycasting/utils.c \
		raycasting/raycasting.c \
		raycasting/player.c \

RAY_DIR = raycasting
OBJ_DIR = obj

OBJ_RAY = $(addprefix $(OBJ_DIR)/,$(SRC_RAY:.c=.o))
OBJ = $(OBJ_RAY)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

# --- macOS ---
MLX_DIR = minilibx_opengl_20191021
MLX_INC = -I ./$(MLX_DIR)
MLX_LIB = ./$(MLX_DIR)/libmlx.a -framework OpenGL -framework AppKit


# --- Linux ---
# MLX_DIR = mlx
# MLX_INC = -I ./$(MLX_DIR)
# MLX_LIB = -L ./mlx -lmlx -lXext -lX11 -lm

# - MLX (macOS/Linux)
INC = -I . -I ./raycasting -I ./libft $(MLX_INC)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) -L ./libft -lft -o $(NAME)

$(LIBFT):
	make -C ./libft all

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	make -C ./libft clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

