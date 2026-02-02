/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:54:22 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/02 18:00:30 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	validation(int argc, char **argv, t_game *game)
{
	int		fd;
	char	*line;

	if (argc != 2)
		print_error("Error: Wrong Arguments.\nUsage: ./cub3D map.cub\n");
	if (!valid_path(argv[1], ".cub"))
		print_error("Error: Invalid path.\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		free_and_print_error(game, "Error: Can't open file.\n");
	line = get_map_lines(fd);
	check_if_file_is_empty(line, game, fd);
	parse_map(game, fd, line);
	map_validation(game);
}
