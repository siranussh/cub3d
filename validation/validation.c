/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:54:22 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/02 16:33:37 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	validation(char **argv, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		free_and_print_error(game, "Error: Can't open file.\n");
	line = get_map_lines(fd);
	check_if_file_is_empty(line, game, fd);
	parse_map(game, fd, line);
	map_validation(game);
}
