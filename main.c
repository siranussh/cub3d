/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:06:35 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/06 14:53:48 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int main(int argc, char **argv)
{
	t_game	*game;

	game = init_game();
	game->map = init_map();
	validation(argc, argv, game);
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
