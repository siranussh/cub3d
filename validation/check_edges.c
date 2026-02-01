/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_edges.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 15:17:24 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/01 15:18:14 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	check_edges(char **map, int map_size, int longest_line)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_size)
	{
		if (map[i][0] != '1' && map[i][0] != '6')
			return (0);
		if (map[i][longest_line - 1] != '1' 
			&& map[i][longest_line - 1] != '6')
			return (0);
		i++;
	}
	j = 0;
	while (j < longest_line)
	{
		if (map[0][j] != '1' && map[0][j] != '6')
			return (0);
		if (map[map_size - 1][j] != '1' 
			&& map[map_size - 1][j] != '6')
			return (0);
		j++;
	}
	return (1);
}
