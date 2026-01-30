/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:25:44 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/30 22:41:48 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "includes/cub3d.h"

void	ft_free(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->no_tx)
		free(map->no_tx);
	if (map->ea_tx)
		free(map->ea_tx);
	if (map->we_tx)
		free(map->we_tx);
	if (map->so_tx)
		free(map->so_tx);
	if (map->param_line)
		free(map->param_line);
	if (map->map_line)
		free(map->map_line);
	if (map->params)
		ft_free(map->params);
	if (map->original_map)
		ft_free(map->original_map);
	if (map->map)
		ft_free(map->map);
	if (map)
		free(map);
}
