/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:53:20 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/14 13:56:56 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	texture_path_len(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (0);
	len = 0;
	i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

char	*get_texture_path(char *map)
{
	char	*path;
	int		texture_len;
	int		i;

	if (!map || !*map)
		return (NULL);
	texture_len = 0;
	while (ft_isspace(*map) == 1)
		map++;
	texture_len = texture_path_len(map);
	if (texture_len == 0)
		return (NULL);
	i = texture_len;
	while (map[i])
	{
		if (!ft_isspace(map[i]))
			return (NULL);
		i++;
	}
	path = (char *)malloc(texture_len + 1);
	if (!path)
		return (NULL);
	ft_memcpy(path, map, texture_len);
	path[texture_len] = '\0';
	return (path);
}

int	if_tx_path_valid(char *path)
{
	int	fd;

	if (!path)
		return (0);
	if (path[0] != '.' && path[1] != '/')
		return (0);
	if (!valid_path(path, ".xpm"))
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
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
