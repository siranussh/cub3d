/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:14:29 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/01 14:29:32 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
			if (map->rect_map[j][i] == 'N' || map->rect_map[j][i] == 'S'
				|| map->rect_map[j][i] == 'E' || map->rect_map[j][i] == 'W')
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
