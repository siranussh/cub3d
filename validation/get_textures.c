/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:51:30 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/11 22:22:03 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
static void	load_texture(t_game *game, t_texture *texture, char *path)
{
	if (!path)
		return ;
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
		&texture->width, &texture->height);
	if (!texture->img)
	{
		free_game(game);
		print_error("Error: Failed to load texture\n");
	}
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
		&texture->size_line, &texture->endian);
	if (!texture->data)
	{
		free_game(game);
		print_error("Error: Failed to get texture data\n");
	}
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->map->no_img, game->map->no_tx);
	load_texture(game, &game->map->ea_img, game->map->ea_tx);
	load_texture(game, &game->map->we_img, game->map->we_tx);
	load_texture(game, &game->map->so_img, game->map->so_tx);
}

int	get_texture_pixel(t_texture *texture, int x, int y)
{
	int		index;
	unsigned int	pixel;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	index = y * texture->size_line + x * (texture->bpp / 8);
	pixel = *(unsigned int *)(texture->data + index);
	return (pixel);
}