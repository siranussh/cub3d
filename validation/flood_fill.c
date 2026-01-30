/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:55:15 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/30 18:27:06 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	flood_fill(t_map *m, char **map, int x, int y)
{
	if (x < 0 || y < 0 || x >= m->map_size || y >= m->longest_line)
	{
		m->is_open = 1;
		return ;
	}
	if (map[x][y] == '0' || map[x][y] == 'N' || map[x][y] == 'S'
		|| map[x][y] == 'E' || map[x][y] == 'W' || map[x][y] == 'C'
		|| map[x][y] == 'O')
	{
		m->is_open = 1;
		return ;
	}
	if (map[x][y] == '1' || map[x][y] == 'F')
		return ;
	if (map[x][y] == 'N' || map[x][y] == 'E'
		|| map[x][y] == 'W' || map[x][y] == 'S')
		map[x][y] = '0';
	if (map[x][y] != '6')
		return ;
	map[x][y] = 'F';
	flood_fill(m, map, x - 1, y);
	flood_fill(m, map, x + 1, y);
	flood_fill(m, map,  x, y - 1);
	flood_fill(m, map, x, y + 1);
}
