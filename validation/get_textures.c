/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:51:30 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/02 13:51:31 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_no_texture(t_map *m, char *map_line)
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

void	get_ea_texture(t_map *m, char *map_line)
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

void	get_we_texture(t_map *m, char *map_line)
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

void	get_so_texture(t_map *m, char *map_line)
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
