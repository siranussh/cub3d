/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:55:56 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/21 18:32:51 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


# define WALL 1
# define EMPTY_SPACE 0
# define NORTH N
# define EAST E
# define WEST W
# define SOUTH S

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
	// char	**map;
	char	*no_tx;
	char	*ea_tx;
	char	*we_tx;
	char	*so_tx;
}	t_map;


// validation_utils.c
int		ft_isspace(int a);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strncpy(char *dest, char *src, int n);

// textures_validation.c
int		texture_path_len(char *str);
char	*get_texture_path(char **map);
int		if_tx_path_valid(char *path);


// read_map.c
char	*get_map_lines(int fd);
// void	parse_map(t_game *game, int fd, char *line);


// error.c
void	print_error(char *str);

// arg_validation.c
int		valid_path(char *path, char *domain);

// validation.c
int		validation(int argc, char **argv);


#endif
