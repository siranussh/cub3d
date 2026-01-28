/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:59:33 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/28 17:34:07 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**copy_map(t_map *m)
{
	int		i;
	int		j;
	int		row_len;
	char	**map_copy;

	if (!m || !m->map)
		return (NULL);
	m->longest_line = maps_longest_line(m->map);
	if (!m->longest_line)
		return (NULL);
	map_copy = (char **)malloc(sizeof(char *) * (m->map_size + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < m->map_size)
	{
		map_copy[i] = (char *)malloc(sizeof(char) * (m->longest_line + 1));
		if (!map_copy[i])
		{
			while (i-- > 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
		row_len = ft_strlen(m->map[i]);
		j = 0;
		while (j < m->longest_line)
		{
			if (j >= row_len || m->map[i][j] == ' ')
				map_copy[i][j] = '6';
			else
				map_copy[i][j] = m->map[i][j];
			j++;
		}
		map_copy[i][j] = '\0';
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

void	map_validation(t_map *m)
{

	char **map_copy;

	map_copy = NULL;
	m->map_size = double_arr_size(m->map);
	if (!check_if_only_ones(m->map, 0)
		|| !check_if_only_ones(m->map, m->map_size - 1))
		free_map_print_error(m, "Error: Map isn't properly enclosed\n");
	if (!if_valid_chars(m->map))
		free_map_print_error(m, "Error: Invalid charecters");
	if (characters_count_check(m->map) != 1)
		free_map_print_error(m,
			"Error: Map must contain one player position\n");
	map_copy = copy_map(m);
	// (void)map_copy;
	int i = 0;
	while (map_copy[i])
	{
		printf("%s\n", map_copy[i]);
		i++;
	}
}
