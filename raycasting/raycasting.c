#include "../includes/cub3d.h"

void put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	*(unsigned int *)(game->data + index) = color;
	// game->data[index] = color & 0xFF;          // Blue
	// game->data[index + 1] = (color >> 8) & 0xFF;  // Green
	// game->data[index + 2] = (color >> 16) & 0xFF; // Red
}

void draw_map(t_game *game)
{
	char	**map = game->map->rect_map;
	int		color = 0x0000FF;

	for (int y = 0; y < game->map->map_size; y++)
		for (int x = 0; x < game->map->longest_line; x++)
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
}


void	clear_image(t_game *game)
{
	ft_bzero(game->data, HEIGHT * game->size_line);
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			put_pixel(x + i, y + j, color, game);
}

t_game *init_game(void)
{
	t_game *game = ft_calloc(1, sizeof(t_game));
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

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (x < 0 || y < 0 || y >= game->map->map_size || x >= game->map->longest_line)
		return (true);
	if (game->map->rect_map[y][x] == '1')
		return (true);
	return (false);
}


float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 -y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

t_ray_info	cast_ray(t_player *player, t_game *game, float angle)
{
	t_ray_info	info;
	float		pos_x;
	float		pos_y;
	float		ray_dir_x;
	float		ray_dir_y;
	int			map_x;
	int			map_y;
	float		delta_dist_x;
	float		delta_dist_y;
	int			step_x;
	int			step_y;
	float		side_dist_x;
	float		side_dist_y;
	int			hit;
	int			side;
	float		perp_dist;
	float		hit_world_x;
	float		wall_pos;

	// DDA raycasting in grid (tile) coordinates for precise wall hits
	pos_x = player->x / (float)BLOCK;
	pos_y = player->y / (float)BLOCK;
	ray_dir_x = cosf(angle);
	ray_dir_y = sinf(angle);
	map_x = (int)floorf(pos_x);
	map_y = (int)floorf(pos_y);
	delta_dist_x = (ray_dir_x == 0.0f) ? 1e30f : fabsf(1.0f / ray_dir_x);
	delta_dist_y = (ray_dir_y == 0.0f) ? 1e30f : fabsf(1.0f / ray_dir_y);
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0f - pos_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0f - pos_y) * delta_dist_y;
	}
	hit = 0;
	side = 0;
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (map_y < 0 || map_x < 0 || map_y >= game->map->map_size
			|| map_x >= game->map->longest_line)
		{
			hit = 1;
			break ;
		}
		if (game->map->rect_map[map_y][map_x] == '1')
			hit = 1;
	}
	if (side == 0)
		perp_dist = (map_x - pos_x + (1 - step_x) / 2.0f)
			/ (ray_dir_x == 0.0f ? 1e-6f : ray_dir_x);
	else
		perp_dist = (map_y - pos_y + (1 - step_y) / 2.0f)
			/ (ray_dir_y == 0.0f ? 1e-6f : ray_dir_y);
	info.dist = perp_dist * BLOCK;
	if (side == 0)
		hit_world_x = player->y + perp_dist * BLOCK * ray_dir_y;
	else
		hit_world_x = player->x + perp_dist * BLOCK * ray_dir_x;
	wall_pos = fmodf(hit_world_x, (float)BLOCK);
	if (wall_pos < 0)
		wall_pos += BLOCK;
	if (side == 0)
	{
		if (ray_dir_x > 0)
			info.texture = &game->map->we_img;
		else
			info.texture = &game->map->ea_img;
	}
	else
	{
		if (ray_dir_y > 0)
			info.texture = &game->map->no_img;
		else
			info.texture = &game->map->so_img;
	}
	info.wall_x = wall_pos;
	return (info);
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

    // Ceiling
    while (++y < start_y)
        put_pixel(i, y, game->map->ceiling_color, game);

    // Wall with texture
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

    // Floor
    while (y < HEIGHT)
        put_pixel(i, y++, game->map->floor_color, game);
}

int draw_loop(t_game *game)
{
    t_player *player = &game->player;
    float fraction = PI / 3 / WIDTH;
    float start_x = player->angle - PI / 6;
    int i = 0;

    move_player(player, game);
    clear_image(game);

    while (i < WIDTH)
    {
        draw_line(player, game, start_x, i);
        start_x += fraction;
        i++;
    }
    mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
    return 0;
}

