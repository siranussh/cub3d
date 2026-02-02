/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:55:56 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/02 13:22:43 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WALL 1
# define EMPTY_SPACE 0
# define NORTH 'N'
# define EAST 'E'
# define WEST 'W'
# define SOUTH 'S'

# include "libft.h"
# include <unistd.h> // close() read()
# include <stdlib.h> // open() malloc() exit()
# include <fcntl.h> // open() flags
# include <stdio.h> // perror()
# include <string.h> // strerror()
# include <sys/time.h> // gettimeofday()
// # include <../mlx/mlx.h>
# include "raycasting.h"

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

/******************* VALIDATION *************************/
// validation_utils.c
int		ft_isspace(int a);
int		str_is_only_spaces(char *str);
char	*ignore_spaces(char *str);
int		find_map_start(char *line);

// read_map.c
char	*get_map_lines(int fd);
void	check_if_file_is_empty(char *line, t_map *m, int fd);

// get_textures_utils.c
int		texture_path_len(char *str);
char	*get_texture_path(char *map);
int		if_tx_path_valid(char *path);

// get_textures.c
void	get_no_texture(t_map *m, char *map_line);
void	get_ea_texture(t_map *m, char *map_line);
void	get_we_texture(t_map *m, char *map_line);
void	get_so_texture(t_map *m, char *map_line);

// get_color.c
void	get_color(t_map *m, char *map_line, char type);
void	get_c_color(t_map *m, char *map_line);
void	get_f_color(t_map *m, char *map_line);

// path_validation.c
int		valid_path(char *path, char *domain);

// flood_fill.c
void	flood_fill(t_map *m, char **map, int y, int x);

// get_position.c
void	player_position(t_map *map);

// parse_map.c
void	parse_params(t_map *m, char *map_line);
void	parse_map(t_map *map, int fd, char *line);

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
void	map_validation(t_map *m);

// validation.c
void		validation(int argc, char **argv, t_map *map);

/**************************************************/

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
void	free_map_print_error(t_map *map, char *str);

#endif
