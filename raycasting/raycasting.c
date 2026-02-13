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

static void	init_dda(t_dda *dda, t_player *player, float angle)
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

static void	calculate_step_and_side_dist(t_dda *dda)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (dda->pos_x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0f - dda->pos_x)
			* dda->delta_dist_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (dda->pos_y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0f - dda->pos_y)
			* dda->delta_dist_y;
	}
}

static int	perform_dda(t_dda *dda, t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (dda->map_y < 0 || dda->map_x < 0 || dda->map_y >= game->map->map_size
			|| dda->map_x >= game->map->longest_line)
			return (1);
		if (game->map->rect_map[dda->map_y][dda->map_x] == '1')
			hit = 1;
	}
	return (hit);
}

static float	calculate_perp_distance(t_dda *dda)
{
	float	perp_dist;

	if (dda->side == 0)
	{
		perp_dist = (dda->map_x - dda->pos_x + (1 - dda->step_x) / 2.0f)
			/ (dda->ray_dir_x == 0.0f ? 1e-6f : dda->ray_dir_x);
	}
	else
	{
		perp_dist = (dda->map_y - dda->pos_y + (1 - dda->step_y) / 2.0f)
			/ (dda->ray_dir_y == 0.0f ? 1e-6f : dda->ray_dir_y);
	}
	return (perp_dist);
}

static void	determine_texture(t_ray_info *info, t_dda *dda, t_game *game)
{
	if (dda->side == 0)
	{
		if (dda->ray_dir_x > 0)
			info->texture = &game->map->we_img;
		else
			info->texture = &game->map->ea_img;
	}
	else
	{
		if (dda->ray_dir_y > 0)
			info->texture = &game->map->no_img;
		else
			info->texture = &game->map->so_img;
	}
}

t_ray_info	cast_ray(t_player *player, t_game *game, float angle)
{
	t_ray_info	info;
	t_dda		dda;
	float		perp_dist;
	float		hit_world_x;
	float		wall_pos;

	init_dda(&dda, player, angle);
	calculate_step_and_side_dist(&dda);
	perform_dda(&dda, game);
	perp_dist = calculate_perp_distance(&dda);
	info.dist = perp_dist * BLOCK;
	if (dda.side == 0)
		hit_world_x = player->y + perp_dist * BLOCK * dda.ray_dir_y;
	else
		hit_world_x = player->x + perp_dist * BLOCK * dda.ray_dir_x;
	wall_pos = fmodf(hit_world_x, (float)BLOCK);
	if (wall_pos < 0)
		wall_pos += BLOCK;
	determine_texture(&info, &dda, game);
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
	t_player	*player = &game->player;
	float		fraction = PI / 3 / WIDTH;
	float		start_x = player->angle - PI / 6;
	int			i = 0;

	move_player(player, game);
	clear_image(game);

	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	return (0);
}

