#include "../includes/cub3d.h"

void draw_map(t_game *game)
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



void draw_square(int x, int y, int size, int color, t_game *game)
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



void draw_line(t_player *player, t_game *game, float angle, int i)
{
    t_ray_info	ray = cast_ray(player, game, angle);
	int			height = (BLOCK / ray.dist) * (HEIGHT / 2);
	int			start_y = (HEIGHT - height) / 2;
	int			end_y = start_y + height;
	int			y = start_y - 1;
	int			tex_y;
	int			tex_x;
	int			color;

	while (++y < start_y)
		put_pixel(i, y, game->map->ceiling_color, game);

	y = start_y - 1;
	tex_x = (int)((ray.wall_x / BLOCK) * ray.texture->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= ray.texture->width)
		tex_x = ray.texture->width - 1;
	while (++y < end_y && ray.texture)
	{
		tex_y = ((y - start_y) * ray.texture->height) / height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= ray.texture->height)
			tex_y = ray.texture->height - 1;
		color = get_texture_pixel(ray.texture, tex_x, tex_y);
		put_pixel(i, y, color, game);
	}
	while (y < HEIGHT)
		put_pixel(i, y++, game->map->floor_color, game);
}

int draw_loop(t_game *game)
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

