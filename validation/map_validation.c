/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:59:33 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/30 21:50:58 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	check_if_only_ones(char **map, int index)
{
	int	j;

	if (!map)
		return (0);
	j = 0;
	while (map[index][j])
	{
		if (map[index][j] != '1' && !ft_isspace(map[index][j]))
			return (0);
		j++;
	}
	return (1);
}

int	if_valid_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	characters_count_check(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	if (!map)
		return (0);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W'
				|| map[i][j] == 'S')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	maps_longest_line(char **map)
{
	int	i;
	int	j;
	int	max_len;

	if (!map)
		return (0);
	i = 0;
	max_len = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > max_len)
			max_len = j;
		i++;
	}
	return (max_len);
}

void	map_validation(t_map *m)
{

	char **map_copy;

	map_copy = NULL;
	m->map_size = double_arr_size(m->original_map);
	if (!check_if_only_ones(m->original_map, 0)
		|| !check_if_only_ones(m->original_map, m->map_size - 1))
		free_map_print_error(m, "Error: Map isn't properly enclosed\n");
	if (!if_valid_chars(m->original_map))
		free_map_print_error(m, "Error: Invalid charecters");
	if (characters_count_check(m->original_map) != 1)
		free_map_print_error(m,
			"Error: Map must contain one player position\n");
	m->map = make_map_rect(m);
	map_copy = copy_map(m);
	// (void)map_copy;
	// int i = 0;
	// while (m->map[i])
	// {
	// 	printf("%s\n", m->map[i]);
	// 	i++;
	// }
	player_position(m);
	flood_fill(m, map_copy, m->player_y, m->player_x);
	if (m->is_open)
		free_map_print_error(m, "Error: Map isn't properly enclosed\n");
}
