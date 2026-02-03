/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:55:56 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/03 12:21:36 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

//linux
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define CLOSE 65307

//macos
// # define W 13
// # define A 0
// # define S 1
// # define D 2

// # define PI 3.14159265359 //for angle calculations
# define PI 3.1415926f

# include "../libft/libft.h"
# include <unistd.h> // close() read()
# include <stdlib.h> // open() malloc() exit()
# include <fcntl.h> // open() flags
# include <stdio.h> // perror()
# include <string.h> // strerror()
# include <sys/time.h> // gettimeofday()
# include <stdbool.h>
# include <math.h>
# include "mlx.h"

typedef struct s_map
{
	char	*no_tx;// no texture path
	char	*ea_tx;// ea texture path
	char	*we_tx;// we texture path
	char	*so_tx;// so texture path
	int		floor_color;
	int		ceiling_color;
	char	*param_line;// textures, colors line
	char	*map_line;// containing only map
	char	**params;// textures, colors
	char	**map;// map for Siran
	char	**rect_map;
	int		map_size;// height
	int		longest_line;// width
	int		is_open;
	int		player_x;
	int		player_y;
}	t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	t_map		*map;
}	t_game;

/******************* VALIDATION *************************/
// validation_utils.c
int		ft_isspace(int a);
int		str_is_only_spaces(char *str);
char	*ignore_spaces(char *str);
int		find_map_start(char *line);

// read_map.c
char	*get_map_lines(int fd);
void	check_if_file_is_empty(char *line, t_game *game, int fd);

// get_textures_utils.c
int		texture_path_len(char *str);
char	*get_texture_path(char *map);
int		if_tx_path_valid(char *path);

// get_textures.c
void	get_no_texture(t_game *game, char *map_line);
void	get_ea_texture(t_game *game, char *map_line);
void	get_we_texture(t_game *game, char *map_line);
void	get_so_texture(t_game *game, char *map_line);

// get_color.c
void	get_color(t_game *game, char *map_line, char type);
void	get_c_color(t_game *game, char *map_line);
void	get_f_color(t_game *game, char *map_line);

// path_validation.c
int		valid_path(char *path, char *domain);

// flood_fill.c
void	flood_fill(t_map *m, char **map, int y, int x);

// get_position.c
void	player_position(t_map *map);

// parse_map.c
void	parse_params(t_game *game, char *map_line);
void	parse_map(t_game *game, int fd, char *line);

// map_validation_utils.c
int		check_if_only_ones(char **map, int index);
int		if_valid_chars(char **map);
int		maps_longest_line(char **map);
int		characters_count_check(char **map);

// check_edges.c
int		check_edges(char **map, int map_size, int longest_line);

// check_space_adjacent.c
int		check_space_adjacent(char **map, int map_size, int longest_line);

// map_manipulation.c
char	**copy_map(t_map *m);
char	**make_map_rect(t_map *m);

// map_validation.c
void	map_validation(t_game *game);

// validation.c
void	validation(int argc, char **argv, t_game *game);

/********************************************************/

/********************* RAYCASTING ***********************/
//player.c
void	init_player(t_player *player);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	move_player(t_player *player, t_game *game);
void	normalize_angle(float *angle);

//raycasting.c
void	put_pixel(int x, int y, int color, t_game *game);
void	clear_image(t_game *game);
void	draw_square(int x, int y, int size, int color, t_game *game);
t_game	*init_game(void);
void	init_mlx(t_game *game);
int		draw_loop(t_game *game);
bool	touch(float px, float py, t_game *game);

//player_movement.c
void	update_player_position(t_player *player, int speed, t_game *game);

//hook.c
int		handle_destroy(t_game *game);
void	free_game(t_game *game);
void	close_game(t_game *game);

/********************************************************/

// utils.c
int		double_arr_size(char **arr);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strncpy(char *dest, char *src, int n);

// init_structs.c
t_map	*init_map(void);

// free.c
void	ft_free(char **str);
void	free_map(t_map *map);

// error_handler.c
void	print_error(char *str);
void	free_and_print_error(t_game *game, char *str);

#endif
