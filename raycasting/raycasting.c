#include "../includes/cub3d.h"

void put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;          // Blue
	game->data[index + 1] = (color >> 8) & 0xFF;  // Green
	game->data[index + 2] = (color >> 16) & 0xFF; // Red
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

float cast_ray(t_player *player, t_game *game, float angle)
{
	float	ray_x = player->x;
	float	ray_y = player->y;
	float	cos_angle = cos(angle);
	float	sin_angle = sin(angle);

	normalize_angle(&player->angle);

	while (!touch(ray_x, ray_y, game))
	{
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	return fixed_dist(player->x, player->y, ray_x, ray_y, game);
}

void draw_line(t_player *player, t_game *game, float angle, int i)
{
    float	dist = cast_ray(player, game, angle);
	int	height = (BLOCK / dist) * (HEIGHT / 2);
	int	start_y = (HEIGHT - height) / 2;
	int	end_y = start_y + height;
	int	y = -1;

    // Ceiling
    while (++y < start_y)
        put_pixel(i, y, game->map->ceiling_color, game);

    // Wall
    while (y < end_y)
        put_pixel(i, y++, 255, game);

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
