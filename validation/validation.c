/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:54:22 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/07 17:16:24 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	validation(int argc, char **argv, t_game *game)
{
	int		fd;
	char	*line;

	if (argc != 2)
		free_and_print_error(game,
			"Error: Wrong Arguments.\nUsage: ./cub3D map.cub\n");
	if (!valid_path(argv[1], ".cub"))
		free_and_print_error(game, "Error: Invalid path.\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		free_and_print_error(game, "Error: Can't open file.\n");
	line = get_map_lines(fd);
	check_if_file_is_empty(line, game, fd);
	parse_map(game, fd, line);
	map_validation(game);
}
