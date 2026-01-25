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
			validation.c

VALID_DIR = validation

OBJ_DIR = obj

OBJ_VALID = $(addprefix $(OBJ_DIR)/$(VALID_DIR)/,$(SRC_VALID:.c=.o))
OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

OBJ = $(OBJ_VALID) $(OBJ_FILES)


CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
# MLX_FLAGS	= -Lmlx -lmlx -lXext -lX11 -lm

LIBFT = ./libft/libft.a

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -I ./includes -I ./libft  $(OBJ) -L ./libft -lft -o $(NAME)
# $(NAME) : $(OBJ) $(LIBFT)
# 	$(CC) $(CFLAGS) -I ./includes -I ./libft  $(OBJ) $(MLX_FLAGS) -L ./libft -lft -o $(NAME)

$(LIBFT) :
	make -C ./libft all

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I ./includes -I ./libft -c $< -o $@

clean :
	make -C ./libft clean
	rm -rf $(OBJ_DIR)

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re