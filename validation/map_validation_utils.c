/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:52:55 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/03 11:40:47 by anavagya         ###   ########.fr       */
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
				&& map[i][j] != ' ' && map[i][j] != '\t')
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
