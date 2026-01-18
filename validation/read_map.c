/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:36:58 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/18 14:00:27 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_map_lines(int fd)
{
	char	*tmp;
	char	*line;

	tmp = NULL;
	line = NULL;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp || tmp[0] == '\n')
		{
			get_next_line(-1);
			if (!tmp)
				break ;
			free(tmp);
			free(line);
			return ("\n");
		}
		if (!line)
			line = ft_gnl_strdup(tmp);
		else
			line = ft_gnl_strjoin(line, tmp);
		free(tmp);
	}
	return (line);
}

void	parse_map(t_game *game, int fd, char *line)
{
	if (!line || !*line)
	{
		close(fd);
		free(line);
		free(game);
		print_error("Error: Map file is empty.\n");
	}
	if (*line == '\n')
	{
		close(fd);
		free(game);
		print_error("Error: Invalid map format.\n");
	}
	game->map = ft_split(line, '\n');
	if (!game->map)
	{
		close(fd);
		free(line);
		free_map(game->map);
		free(game);
		print_error("Error: Invalid map format or malloc error.\n");
	}
}

void	validate_map(t_game *game, int fd, char *line)
{
	if (!valid_map(game, game->map))
	{
		close(fd);
		free(line);
		free_map(game->map);
		free(game);
		exit(1);
	}
	if (!check_reachability(game))
	{
		close(fd);
		free(line);
		free_map(game->map);
		free(game);
		print_error("Error: Map has unreachable collectibles or exit.\n");
	}
	if (!map_size(game))
	{
		close(fd);
		free(line);
		free_map(game->map);
		free(game);
		print_error("Error: Map is too big.\n");
	}
}

char	**load_map(t_game *game, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(game);
		print_error("Error: Can't open file.\n");
	}
	line = get_map_lines(fd);
	parse_map(game, fd, line);
	game->width = ft_strlen(game->map[0]);
	while (game->map[game->height])
		game->height++;
	validate_map(game, fd, line);
	close(fd);
	free(line);
	return (game->map);
}
