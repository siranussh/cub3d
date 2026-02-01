/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:59:33 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/01 13:47:11 by anavagya         ###   ########.fr       */
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

int	check_edges(t_map *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->map_size)
	{
		if (m->map[i][0] != '1' && m->map[i][0] != '6')
			return (0);
		if (m->map[i][m->longest_line - 1] != '1' 
			&& m->map[i][m->longest_line - 1] != '6')
			return (0);
		i++;
	}
	j = 0;
	while (j < m->longest_line)
	{
		if (m->map[0][j] != '1' && m->map[0][j] != '6')
			return (0);
		if (m->map[m->map_size - 1][j] != '1' 
			&& m->map[m->map_size - 1][j] != '6')
			return (0);
		j++;
	}
	return (1);
}

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_space_adjacent(t_map *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->map_size)
	{
		j = 0;
		while (j < m->longest_line)
		{
			if (m->map[i][j] == '6' || m->map[i][j] == ' ')
			{
				if ((i > 0 && is_walkable(m->map[i - 1][j]))
					|| (i < m->map_size - 1 && is_walkable(m->map[i + 1][j]))
					|| (j > 0 && is_walkable(m->map[i][j - 1]))
					|| (j < m->longest_line - 1 && is_walkable(m->map[i][j + 1])))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
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
	if (!check_edges(m))
		free_map_print_error(m, "Error: Map isn't properly enclosed\n");
	if (!check_space_adjacent(m))
		free_map_print_error(m, "Error: Map isn't properly enclosed\n");
	player_position(m);
	map_copy = copy_map(m);
	m->is_open = 0;
	flood_fill(m, map_copy, m->player_y, m->player_x);
	ft_free(map_copy);
	if (m->is_open)
		free_map_print_error(m, "Error: Map isn't properly enclosed\n");
}

