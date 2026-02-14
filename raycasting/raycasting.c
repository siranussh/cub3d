/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:11:04 by sihakoby          #+#    #+#             */
/*   Updated: 2026/02/14 13:42:48 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		x;
	int		y;

	y = 0;
	color = 0x0000FF;
	map = game->map->rect_map;
	while (y < game->map->map_size)
	{
		x = 0;
		while (x < game->map->longest_line)
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
			x++;
		}
		y++;
	}
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(x + i, y + j, color, game);
			j++;
		}
		i++;
	}
}

void	draw_line(t_player *player, t_game *game, float angle, int i)
{
	t_ray_info	ray;
	int			height;
	int			start_y;
	int			end_y;

	ray = cast_ray(player, game, angle);
	ray.game = game;
	height = (BLOCK / ray.dist) * (HEIGHT / 2);
	start_y = (HEIGHT - height) / 2;
	end_y = start_y + height;
	draw_ceiling(i, start_y, game);
	draw_wall(i, start_y, end_y, &ray);
	draw_floor(i, end_y, game);
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	fraction = PI / 3 / WIDTH;
	player = &game->player;
	start_x = player->angle - PI / 6;
	i = 0;
	move_player(player, game);
	ft_bzero(game->data, HEIGHT * game->size_line);
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	return (0);
}
