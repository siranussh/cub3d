/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:51:58 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/07 16:00:43 by anavagya         ###   ########.fr       */
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
		while (i < (int)ft_strlen(map->rect_map[j]))
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
