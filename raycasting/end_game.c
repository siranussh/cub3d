/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:10:52 by sihakoby          #+#    #+#             */
/*   Updated: 2026/02/14 13:11:48 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_destroy(t_game *game)
{
	free_game(game);
	exit(0);
}

void	destroy_textures(t_game *game)
{
	if (game->map->no_img.img)
		mlx_destroy_image(game->mlx, game->map->no_img.img);
	if (game->map->ea_img.img)
		mlx_destroy_image(game->mlx, game->map->ea_img.img);
	if (game->map->we_img.img)
		mlx_destroy_image(game->mlx, game->map->we_img.img);
	if (game->map->so_img.img)
		mlx_destroy_image(game->mlx, game->map->so_img.img);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map && game->mlx)
		destroy_textures(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free_map(game->map);
	if (game)
		free(game);
}

void	close_game(t_game *game)
{
	if (!game)
		exit(0);
	if (game->map && game->mlx)
		destroy_textures(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free_map(game->map);
	if (game)
		free(game);
	exit(0);
}
