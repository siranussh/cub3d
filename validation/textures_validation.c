/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:56:57 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/23 20:25:49 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

static void	check_no_texture(t_map *m, char *map_line)
{
	if (m->no_tx)
	{
		free_map(m);
		print_error("Error: Duplicate NO texture\n");
	}
	map_line += 2;
	map_line = ignore_spaces(map_line);
	m->no_tx = get_texture_path(map_line);
	if (!if_tx_path_valid(m->no_tx))
	{
		free_map(m);
		print_error("Error: Invalid NO texture\n");
	}
}

static void	check_ea_texture(t_map *m, char *map_line)
{
	if (m->ea_tx)
	{
		free_map(m);
		print_error("Error: Duplicate EA texture\n");
	}
	map_line += 2;
	map_line = ignore_spaces(map_line);
	m->ea_tx = get_texture_path(map_line);
	if (!if_tx_path_valid(m->ea_tx))
	{
		free_map(m);
		print_error("Error: Invalid EA texture\n");
	}
}

static void	check_we_texture(t_map *m, char *map_line)
{
	if (m->we_tx)
	{
		free_map(m);
		print_error("Error: Duplicate WE texture\n");
	}
	map_line += 2;
	map_line = ignore_spaces(map_line);
	m->we_tx = get_texture_path(map_line);
	if (!if_tx_path_valid(m->we_tx))
	{
		free_map(m);
		print_error("Error: Invalid WE texture\n");
	}
}

static void	check_so_texture(t_map *m, char *map_line)
{
	if (m->so_tx)
	{
		free_map(m);
		print_error("Error: Duplicate SO texture\n");
	}
	map_line += 2;
	map_line = ignore_spaces(map_line);
	m->so_tx = get_texture_path(map_line);
	if (!if_tx_path_valid(m->so_tx))
	{
		free_map(m);	
		print_error("Error: Invalid SO texture\n");
	}
}

void	parse_news(t_map *m, char *map_line)
{
	char	*trimmed;

	trimmed = ignore_spaces(map_line);
	if (ft_strncmp(trimmed, "NO", 2) == 0)
		check_no_texture(m, trimmed);
	else if(ft_strncmp(trimmed, "EA", 2) == 0)
		check_ea_texture(m, trimmed);
	else if (ft_strncmp(trimmed, "WE", 2) == 0)
		check_we_texture(m, trimmed);
	else if(ft_strncmp(trimmed, "SO", 2) == 0)
		check_so_texture(m, trimmed);
	else
	{
		free_map(m);
		print_error("Error: Invalid map\n");
	}
}
