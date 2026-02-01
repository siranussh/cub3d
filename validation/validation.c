/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:54:22 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/01 15:12:48 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	validation(int argc, char **argv)
{
	t_map	*map;
	int		fd;
	char	*line;

	if (argc != 2)
		print_error("Error: Wrong Arguments.\nUsage: ./cub3D map.cub\n");
	if (!valid_path(argv[1], ".cub"))
		print_error("Error: Invalid path.\n");
	map = init_map();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		free_map_print_error(map, "Error: Can't open file.\n");
	line = get_map_lines(fd);
	check_if_file_is_empty(line, map, fd);
	parse_map(map, fd, line);
	map_validation(map);
	free_map(map);// hanel
}
