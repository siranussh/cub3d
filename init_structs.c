/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:43:39 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/29 15:11:25 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		print_error("Error: malloc failed/n");
	map->no_tx = NULL;
	map->ea_tx = NULL;
	map->we_tx = NULL;
	map->so_tx = NULL;
	map->param_line = NULL;
	map->map_line = NULL;
	map->params = NULL;
	map->map = NULL;
	map->map_size = 0;
	map->longest_line = 0;
	map->is_open = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->floor_color = -1;
	map->ceiling_color = -1;
	return (map);
}
