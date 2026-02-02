NAME = cub3D

SRC_FILES = utils.c \
			init_structs.c \
			error_handler.c \
			free.c \
			main.c

SRC_VALID = read_map.c \
			path_validation.c \
			validation_utils.c \
			get_textures_utils.c \
			get_textures.c \
			get_color.c \
			parse_map.c \
			flood_fill.c \
			get_position.c \
			map_manipulation.c \
			map_validation_utils.c \
			check_edges.c \
			check_space_adjacent.c \
			map_validation.c \
			validation.c

SRC_RAYCASTING = raycasting.c \
				player.c \
				player_movement.c \
				hook.c \

VALID_DIR = validation
RAYCASTING_DIR = raycasting

OBJ_DIR = obj

OBJ_VALID = $(addprefix $(OBJ_DIR)/$(VALID_DIR)/,$(SRC_VALID:.c=.o))
OBJ_RAYCASTING = $(addprefix $(OBJ_DIR)/$(RAYCASTING_DIR)/,$(SRC_RAYCASTING:.c=.o))
OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

OBJ = $(OBJ_VALID) $(OBJ_FILES) $(OBJ_RAYCASTING)


CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

MLX_DIR = mlx
MLX_FLAGS = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm

INC = -I ./includes -I . -I ./raycasting -I ./libft -I ./mlx

LIBFT = ./libft/libft.a

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(MLX_FLAGS) -L ./libft -lft -o $(NAME)

$(LIBFT) :
	make -C ./libft all

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	make -C ./libft clean
	rm -rf $(OBJ_DIR)

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
