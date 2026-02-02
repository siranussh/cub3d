/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:59:33 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/02 12:20:12 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_validation(t_map *m)
{
	char **map_copy;

	map_copy = NULL;
	m->map_size = double_arr_size(m->map);
	if (!check_if_only_ones(m->map, 0)
		|| !check_if_only_ones(m->map, m->map_size - 1))
		free_map_print_error(m, "Error: Map isn't properly enclosed\n");
	if (!if_valid_chars(m->map))
		free_map_print_error(m, "Error: Invalid charecters\n");
	if (characters_count_check(m->map) != 1)
		free_map_print_error(m,
			"Error: Map must contain one player position\n");
	m->rect_map = make_map_rect(m);
	if (!check_edges(m->rect_map, m->map_size, m->longest_line))
		free_map_print_error(m, "Error: Map isn't properly enclosed\n");
	if (!check_space_adjacent(m->rect_map, m->map_size, m->longest_line))
		free_map_print_error(m, "Error: Map isn't properly enclosed\n");
	player_position(m);
	map_copy = copy_map(m);
	m->is_open = 0;
	flood_fill(m, map_copy, m->player_y, m->player_x);
	ft_free(map_copy);
	if (m->is_open)
		free_map_print_error(m, "Error: Map isn't properly enclosed\n");
}

