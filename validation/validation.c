/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:54:22 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/23 18:44:42 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	validation(int argc, char **argv)
{
	t_map	*map;
	int		fd;
	char	*line;

	if (argc > 2)
		print_error("Error: Wrong Arguments.\nUsage: ./cub3D map.cub\n");
	if (!valid_path(argv[1], ".cub"))
		print_error("Error: Invalid path.\n");
	// init map structure
	map = init_map();
	fd = open(argv[1], O_RDONLY);
	line = get_map_lines(fd);
	parse_map(map, fd, line);
	// printf("line======%s", line);/////////
	
	// 1.	split with '\n'
	// 
	// 2.	check each texture path's validation
	//	 	store textuer paths in t_map
	// 
	// 3.	check colors validation
	//		floor ceiling colors
	// 
	// 4.	store map
	// 		heck map's validation
	return (1);
}
