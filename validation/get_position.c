/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:14:29 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/29 15:46:37 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_position(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->map_size)
	{
		i = 0;
		while (i < map->longest_line)
		{
			if (map->map[j][i] == 'N' || map->map[j][i] == 'S'
				|| map->map[j][i] == 'E' || map->map[j][i] == 'W')
			{
				map->player_x = i;
				map->player_y = j;
				return ;
			}
			i++;
		}
		j++;
	}
}
