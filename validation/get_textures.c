/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:52:25 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/14 13:56:46 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_no_texture(t_game *game, char *map_line)
{
	if (game->map->no_tx)
	{
		free_game(game);
		print_error("Error: Duplicate NO texture\n");
	}
	map_line += 2;
	map_line = ignore_spaces(map_line);
	game->map->no_tx = get_texture_path(map_line);
	if (!if_tx_path_valid(game->map->no_tx))
	{
		free_game(game);
		print_error("Error: Invalid NO texture\n");
	}
}

void	get_ea_texture(t_game *game, char *map_line)
{
	if (game->map->ea_tx)
	{
		free_game(game);
		print_error("Error: Duplicate EA texture\n");
	}
	map_line += 2;
	map_line = ignore_spaces(map_line);
	game->map->ea_tx = get_texture_path(map_line);
	if (!if_tx_path_valid(game->map->ea_tx))
	{
		free_game(game);
		print_error("Error: Invalid EA texture\n");
	}
}

void	get_we_texture(t_game *game, char *map_line)
{
	if (game->map->we_tx)
	{
		free_game(game);
		print_error("Error: Duplicate WE texture\n");
	}
	map_line += 2;
	map_line = ignore_spaces(map_line);
	game->map->we_tx = get_texture_path(map_line);
	if (!if_tx_path_valid(game->map->we_tx))
	{
		free_game(game);
		print_error("Error: Invalid WE texture\n");
	}
}

void	get_so_texture(t_game *game, char *map_line)
{
	if (game->map->so_tx)
	{
		free_game(game);
		print_error("Error: Duplicate SO texture\n");
	}
	map_line += 2;
	map_line = ignore_spaces(map_line);
	game->map->so_tx = get_texture_path(map_line);
	if (!if_tx_path_valid(game->map->so_tx))
	{
		free_game(game);
		print_error("Error: Invalid SO texture\n");
	}
}

int	get_texture_pixel(t_texture *texture, int x, int y)
{
	int				index;
	unsigned int	pixel;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	index = y * texture->size_line + x * (texture->bpp / 8);
	pixel = *(unsigned int *)(texture->data + index);
	return (pixel);
}
