/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:55:56 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/25 17:04:57 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
#include <sys/time.h> // gettimeofday()
// # include <../mlx/mlx.h>

typedef struct s_map
{
	char	*no_tx;
	char	*ea_tx;
	char	*we_tx;
	char	*so_tx;
	int		floor_color;
	int		ceiling_color;
	char	*param_line;// textures, colors line
	char	*map_line;// containing only map
	char	**params;// textures, colors
	char	**map;// only the map
	int		map_size;//????
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

// textures_validation_utils.c
int		texture_path_len(char *str);
char	*get_texture_path(char *map);
int		if_tx_path_valid(char *path);

// texture_validation.c
void	parse_news(t_map *m, char *map_line);

// get_color.c
int		double_arr_size(char **arr);
void	get_color(t_map *m, char *map_line, char type);
void	parse_colors(t_map *m, char *map_line);

// path_validation.c
int		valid_path(char *path, char *domain);

// parse_map.c
void	parse_map(t_map *map, int fd, char *line);


// validation.c
int		validation(int argc, char **argv);

/**************************************************/

// utils.c
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
