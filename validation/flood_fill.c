/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:51:46 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/20 13:09:49 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	flood_fill(t_map *m, char **map, int y, int x)
{
	if (y < 0 || x < 0 || y >= m->map_size || x >= m->longest_line)
	{
		m->is_open = 1;
		return ;
	}
	if (map[y][x] == '6' || map[y][x] == ' ')
	{
		m->is_open = 1;
		return ;
	}
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] != '0' && map[y][x] != 'N' && map[y][x] != 'S'
		&& map[y][x] != 'E' && map[y][x] != 'W')
		return ;
	map[y][x] = 'F';
	flood_fill(m, map, y - 1, x);
	flood_fill(m, map, y + 1, x);
	flood_fill(m, map, y, x - 1);
	flood_fill(m, map, y, x + 1);
}
