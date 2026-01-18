/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:55:56 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/18 13:57:48 by anavagya         ###   ########.fr       */
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
# include <../mlx/mlx.h>

// read_map.c


// error.c
void	print_error(char *str);

// validation.c
int		validation(int argc, char **argv);


#endif
