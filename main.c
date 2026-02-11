/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:06:35 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/11 13:16:20 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	update_player_values(t_game *game)
{
	char map_c;

	game->player.x = game->map->player_x * BLOCK + BLOCK / 2;
	game->player.y = game->map->player_y * BLOCK + BLOCK / 2;
	map_c = game->map->rect_map[game->map->player_y][game->map->player_x];
	if (map_c == 'N')
		game->player.angle = 3 * PI / 2;
	else if (map_c == 'S')
		game->player.angle = PI / 2;
	else if (map_c == 'E')
		game->player.angle = 0;
	else if (map_c == 'W')
		game->player.angle = PI;
	game->map->rect_map[game->map->player_y][game->map->player_x] = '0';
}


int main(int argc, char **argv)
{
	t_game	*game;

	game = init_game();
	game->map = init_map();
	validation(argc, argv, game);
	update_player_values(game);
	init_mlx(game);
	// mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	mlx_hook(game->window, 2, 1L<<0, key_press, game);//1L<<0 this is bitmask for key press
	mlx_hook(game->window, 3, 1L<<1, key_release, game);//1L<<1 this is bitmask for key press
	mlx_hook(game->window, 17, 0, handle_destroy, game);
	// mlx_put_image_to_window(game.mlx, game.window, game.img, 0, 0);//macos version
	// draw_square(WIDTH / 2, HEIGHT / 2, 10, 0x00FF00, &game);
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_loop(game->mlx);
}
