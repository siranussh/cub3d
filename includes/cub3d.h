/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:55:56 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/14 13:58:41 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define CLOSE 65307

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

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_map
{
	char		*no_tx;
	char		*ea_tx;
	char		*we_tx;
	char		*so_tx;
	t_texture	no_img;
	t_texture	ea_img;
	t_texture	we_img;
	t_texture	so_img;
	int			floor_color;
	int			ceiling_color;
	char		*param_line;
	char		*map_line;
	char		**params;
	char		**map;
	char		**rect_map;
	int			map_size;
	int			longest_line;
	int			is_open;
	int			player_x;
	int			player_y;
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

typedef struct s_ray_info
{
	float		dist;
	t_texture	*texture;
	float		wall_x;
	t_game		*game;
}	t_ray_info;

typedef struct s_dda
{
	float	pos_x;
	float	pos_y;
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;
	int		side;
}	t_dda;

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
void	load_textures(t_game *game);

// get_textures.c
void	get_no_texture(t_game *game, char *map_line);
void	get_ea_texture(t_game *game, char *map_line);
void	get_we_texture(t_game *game, char *map_line);
void	get_so_texture(t_game *game, char *map_line);
int		get_texture_pixel(t_texture *texture, int x, int y);

// get_color_utils.c
int		check_rgb(char **rgb);
int		count_commas(char *line);
int		is_only_digits(char *color_rgb);

// get_color.c
int		parse_rgb(t_game *game, char *map_line);
void	get_color(t_game *game, char *line, char type);
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

// convert_spaces.c
void	convert_enclosed_spaces(t_map *m);

// map_validation.c
void	map_validation(t_game *game);

// validation.c
void	validation(int argc, char **argv, t_game *game);

/********************************************************/

/********************* RAYCASTING ***********************/
//player.c
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	move_player(t_player *player, t_game *game);
void	normalize_angle(float *angle);

//raycasting.c
void	put_pixel(int x, int y, int color, t_game *game);
void	draw_square(int x, int y, int size, int color, t_game *game);
int		draw_loop(t_game *game);
bool	touch(float px, float py, t_game *game);

//player_movement.c
void	update_player_position(t_player *player, int speed, t_game *game);

//hook.c
int		handle_destroy(t_game *game);
void	free_game(t_game *game);
void	close_game(t_game *game);

//dda.c
t_ray_info	cast_ray(t_player *player, t_game *game, float angle);

//draw_utils
void	put_pixel(int x, int y, int color, t_game *game);
bool	touch(float px, float py, t_game *game);
int		get_texture_x(float wall_x, t_ray_info *ray);
int		get_texture_y(int y, int start_y, int height, t_ray_info *ray);

//draw.c
void	draw_ceiling(int column, int start_y, t_game *game);
void	draw_wall(int column, int start_y, int end_y, t_ray_info *ray);
void	draw_floor(int column, int end_y, t_game *game);
/********************************************************/

// utils.c
int		double_arr_size(char **arr);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strncpy(char *dest, char *src, int n);

// init_structs.c
t_map	*init_map(void);
void	init_dda(t_dda *dda, t_player *player, float angle);
t_game	*init_game(void);
void	init_mlx(t_game *game);
void	init_player(t_player *player);

// free.c
void	ft_free(char **str);
void	free_map(t_map *map);

// error_handler.c
void	print_error(char *str);
void	free_and_print_error(t_game *game, char *str);

#endif
