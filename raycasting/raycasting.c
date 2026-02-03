#include "../includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;//in which position in memory is the pixel(x, y) we convert 2d(x,y) -> to 1D index
	game->data[index] = color & 0xFF;//blue
	game->data[index + 1] = (color >> 8) & 0xFF;//green
	game->data[index + 2] = (color >> 16) & 0xFF;//red  this just writes the color bytes into memory
}

void	draw_map(t_game *game)
{
	char	**map = game->map->map;
	int		color = 0x0000FF;
	int		y;
	int		x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * 64, y * 64, 64, color, game);
			x++;
		}
		y++;
	}
}

void	clear_image(t_game *game)
{
// 	int y;
// 	int x;

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			put_pixel(x, y, 0, game);
// 			x++;
// 		}
// 		y++;
	ft_bzero(game->data, HEIGHT * game->size_line);
}
//to draw pixels/squares in an MLX image
void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(x + i, y, color, game);
	i = -1;
	while(++i < size)
		put_pixel(x, y + i, color, game);
	i = -1;
	while (++i < size)
		put_pixel(x +  size - 1, y + i, color, game);
	i = -1;
	while (++i < size)
		put_pixel(x + i, y + size - 1, color, game);
}

char	**get_map(void)
{
	char	**map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000000001";
	map[3] = "100000100000001";
	map[4] = "100000000000001";
	map[5] = "100000010000001";
	map[6] = "100001000000001";
	map[7] = "100000000000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
}

//creating window for game with size we prefer
/*ray is a imaginary straight line goinf=g in a specific direction until it hits a wall*/
//raycasting is throwing many rays ...🦗
//game->data is a 1D array of bytes
t_game	*init_game(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		print_error("Error: malloc failed/n");

	init_player(&game->player);
	// game->map->map = get_map();
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
	if (x < 0 || y < 0)
		return (true);
	if (!game->map->map[y] || !game->map->map[y][x])
		return (true);
	if (game->map->map[y][x] == '1')
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

// void draw_line(t_player *player, t_game *game, float start_x, int i)
// {
// 	float cos_angle;
// 	float sin_angle;
// 	float ray_x;
// 	float ray_y;

// 	cos_angle = cos(start_x);
// 	sin_angle = sin(start_x);
// 	ray_x = player->x;
// 	ray_y = player->y;

// 	while(!touch(ray_x, ray_y, game))
// 	{
// 		// put_pixel(ray_x, ray_y, 0xFF0000, game);
// 		ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}
// 	float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
//     float height = (BLOCK / dist) * (WIDTH / 2);
//     int start_y = (HEIGHT - height) / 2;
//     int end = start_y + height; //each ray draws one vertical wall slice, close wall->short,
// 	while(start_y < end)
// 	{
// 		put_pixel(i, start_y, 255, game);
// 		start_y++;
// 	}
// }

float	cast_ray(t_player *player, t_game *game, float angle)
{
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;


	normalize_angle(&player->angle);
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	ray_x = player->x;
	ray_y = player->y;

	while (!touch(ray_x, ray_y, game))
	{
		// put_pixel(ray_x, ray_y, 0xFF0000, game); // optional debug
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	return (fixed_dist(player->x, player->y, ray_x, ray_y, game));
}

void	draw_line(t_player *player, t_game *game, float angle, int i)
{
	float	dist;
	int		start_y;
	int		end_y;
	int		height;
	int		y;

	dist = cast_ray(player, game, angle);
	height = (BLOCK / dist) * (HEIGHT / 2);
	start_y = (HEIGHT - height) / 2;
	end_y = start_y + height;
	y = -1;
	while (++y < start_y)//ceiling
		put_pixel(i, y, game->map->ceiling_color, game);
	while (y < end_y)//wall
	{
		put_pixel(i, y, 255, game);
		y++;
	}
	while (y < HEIGHT)//floor
	{
		put_pixel(i, y, game->map->floor_color, game);
		y++;
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	move_player(player, game);
	clear_image(game);
	// draw_square(player->x, player->y, 10, 0x00FF00, game);
	// draw_map(game);
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6; //PI 180 start_x = 30
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	return (0);
}
