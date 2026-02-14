/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:43:39 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/14 13:08:24 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
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
	map->rect_map = NULL;
	map->map_size = 0;
	map->longest_line = 0;
	map->is_open = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->floor_color = -1;
	map->ceiling_color = -1;
	return (map);
}

 void	init_dda(t_dda *dda, t_player *player, float angle)
{
	dda->pos_x = player->x / (float)BLOCK;
	dda->pos_y = player->y / (float)BLOCK;
	dda->ray_dir_x = cosf(angle);
	dda->ray_dir_y = sinf(angle);
	dda->map_x = (int)floorf(dda->pos_x);
	dda->map_y = (int)floorf(dda->pos_y);
	if (dda->ray_dir_x == 0.0f)
		dda->delta_dist_x = 1e30f;
	else
		dda->delta_dist_x = fabsf(1.0f / dda->ray_dir_x);
	if (dda->ray_dir_y == 0.0f)
		dda->delta_dist_y = 1e30f;
	else
		dda->delta_dist_y = fabsf(1.0f / dda->ray_dir_y);
}

t_game *init_game(void)
{
	t_game *game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		print_error("Error: malloc failed\n");
	init_player(&game->player);
	return (game);
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		free_and_print_error(game, "mlx_init failed\n");
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	if (!game->window)
		free_and_print_error(game, "mlx_new_window failed\n");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		free_and_print_error(game, "mlx_new_image failed\n");
	game->data = mlx_get_data_addr(
		game->img, &game->bpp, &game->size_line, &game->endian);
	if (!game->data)
		free_and_print_error(game, "mlx_get_data_addr failed\n");
	load_textures(game);
}

void	init_player(t_player *player)
{
	player->x = -1;
	player->y = -1;
	player->angle = 0;
	player->key_up = false;
	player->key_left = false;
	player->key_right = false;
	player->key_down = false;
	player->left_rotate = false;
	player->right_rotate = false;
}