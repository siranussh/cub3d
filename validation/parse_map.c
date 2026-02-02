/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:10:13 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/02 16:28:01 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_params(t_game *game, char *map_line)
{
	char	*trimmed;

	trimmed = ignore_spaces(map_line);
	if (ft_strncmp(trimmed, "NO", 2) == 0)
		get_no_texture(game, trimmed);
	else if (ft_strncmp(trimmed, "EA", 2) == 0)
		get_ea_texture(game, trimmed);
	else if (ft_strncmp(trimmed, "WE", 2) == 0)
		get_we_texture(game, trimmed);
	else if (ft_strncmp(trimmed, "SO", 2) == 0)
		get_so_texture(game, trimmed);
	else if (ft_strncmp(trimmed, "C", 1) == 0)
		get_c_color(game, trimmed);
	else if (ft_strncmp(trimmed, "F", 1) == 0)
		get_f_color(game, trimmed);
	else if (str_is_only_spaces(trimmed))
		return ;
	else
	{
		free_game(game);
		print_error("Error: Invalid map\n");
	}
}

void	ensure_no_empty_map_lines(t_game *game, const char *map_line)
{
	int	i;
	int	line_has_content;

	i = 0;
	line_has_content = 0;
	while (map_line && map_line[i])
	{
		line_has_content = 0;
		while (map_line[i] && map_line[i] != '\n')
		{
			if (!ft_isspace(map_line[i]))
				line_has_content = 1;
			i++;
		}
		if (!line_has_content)
			free_and_print_error(game, "Error: Empty line inside map\n");
		if (map_line[i] == '\n')
			i++;
	}
}

void	parse_map(t_game *game, int fd, char *line)
{
	int		i;
	int		index;

	i = 0;
	index = find_map_start(line);
	game->map->param_line = ft_substr(line, 0, index - 1);
	game->map->map_line = ft_substr(line, index, ft_strlen(line));
	free(line);
	close(fd);
	ensure_no_empty_map_lines(game, game->map->map_line);
	game->map->params = ft_split(game->map->param_line, '\n');
	i = 0;
	while (game->map->params[i])
	{
		parse_params(game, game->map->params[i]);
		i++;
	}
	if (!game->map->no_tx || !game->map->ea_tx || !game->map->we_tx || !game->map->so_tx)
		free_and_print_error(game, "Error: Missing texture\n");
	if (game->map->floor_color == -1 || game->map->ceiling_color == -1)
		free_and_print_error(game, "Error: Missing floor or ceiling color\n");
	game->map->map = ft_split(game->map->map_line, '\n');
	if (!game->map->map || !*(game->map->map))
		free_and_print_error(game, "Error: Map doesn't exist\n");
}
