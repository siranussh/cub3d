/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:10:49 by sihakoby          #+#    #+#             */
/*   Updated: 2026/02/14 13:30:25 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_ceiling(int column, int start_y, t_game *game)
{
	int	y;

	y = -1;
	while (++y < start_y)
		put_pixel(column, y, game->map->ceiling_color, game);
}

void	draw_wall(int column, int start_y, int end_y, t_ray_info *ray)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;
	int	height;

	if (!ray || !ray->texture || !ray->game)
		return ;
	height = end_y - start_y;
	tex_x = get_texture_x(ray->wall_x, ray);
	y = start_y - 1;
	while (++y < end_y && ray->texture)
	{
		tex_y = get_texture_y(y, start_y, height, ray);
		color = get_texture_pixel(ray->texture, tex_x, tex_y);
		put_pixel(column, y, color, ray->game);
	}
}

void	draw_floor(int column, int end_y, t_game *game)
{
	int	y;

	y = end_y - 1;
	while (++y < HEIGHT)
		put_pixel(column, y, game->map->floor_color, game);
}
