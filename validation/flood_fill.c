/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:55:15 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/28 18:20:07 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	flood_fill(t_map *m, int x, int y)
{
	if (x < 0 || y < 0 || x >= m->map_size || y >= m->longest_line)
		return ;
	if (m->map[x][y] == 'N' || m->map[x][y] == 'E'
		|| m->map[x][y] == 'W' || m->map[x][y] == 'S')
		m->map[x][y] = '0';
	if (m->map[x][y] == '1' || m->map[x][y] == 'F')
		return ;
	if (m->map[x][y] != '0')
		return ;
	m->map[x][y] = 'F';
	flood_fill(m, x - 1, y);
	flood_fill(m, x + 1, y);
	flood_fill(m,  x, y - 1);
	flood_fill(m, x, y + 1);
}
