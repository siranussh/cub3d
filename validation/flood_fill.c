/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:55:15 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/26 12:55:44 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	flood_fill(char **map, t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->height || y >= game->width)
		return ;
	if (map[x][y] == 'C' || map[x][y] == 'P')
		map[x][y] = '0';
	if (map[x][y] == '1' || map[x][y] == 'F')
		return ;
	if (map[x][y] == 'E')
	{
		map[x][y] = '1';
		return ;
	}
	if (map[x][y] != '0')
		return ;
	map[x][y] = 'F';
	flood_fill(map, game, x - 1, y);
	flood_fill(map, game, x + 1, y);
	flood_fill(map, game, x, y - 1);
	flood_fill(map, game, x, y + 1);
}
