/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:59:33 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/06 17:20:22 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_validation(t_game *game)
{
	char	**map_copy;

	game->map->map_size = double_arr_size(game->map->map);
	if (!check_if_only_ones(game->map->map, 0)
		|| !check_if_only_ones(game->map->map, game->map->map_size - 1))
		free_and_print_error(game, "Error: Map isn't properly enclosed\n");
	if (!if_valid_chars(game->map->map))
		free_and_print_error(game, "Error: Invalid charecters\n");
	if (characters_count_check(game->map->map) != 1)
		free_and_print_error(game,
			"Error: Map must contain one player position\n");
	game->map->rect_map = make_map_rect(game->map);
	convert_enclosed_spaces(game->map);
	if (!check_edges(game->map->rect_map, game->map->map_size,
			game->map->longest_line))
		free_and_print_error(game, "Error: Map isn't properly enclosed\n");
	if (!check_space_adjacent(game->map->rect_map, game->map->map_size,
			game->map->longest_line))
		free_and_print_error(game, "Error: Map isn't properly enclosed\n");
	player_position(game->map);
	map_copy = copy_map(game->map);
	game->map->is_open = 0;
	flood_fill(game->map, map_copy, game->map->player_y, game->map->player_x);
	ft_free(map_copy);
	if (game->map->is_open)
		free_and_print_error(game, "Error: Map isn't properly enclosed\n");
}
