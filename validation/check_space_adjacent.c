/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space_adjacent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 15:15:26 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/01 15:16:31 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_space_adjacent(char **map, int map_size, int longest_line)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_size)
	{
		j = 0;
		while (j < longest_line)
		{
			if (map[i][j] == '6' || map[i][j] == ' ')
			{
				if ((i > 0 && is_walkable(map[i - 1][j]))
					|| (i < map_size - 1 && is_walkable(map[i + 1][j]))
					|| (j > 0 && is_walkable(map[i][j - 1]))
					|| (j < longest_line - 1 && is_walkable(map[i][j + 1])))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
