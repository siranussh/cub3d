#include "../includes/cub3d.h"

void put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	*(unsigned int *)(game->data + index) = color;
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


int	get_texture_x(float wall_x, t_ray_info *ray)
{
	int	tex_x;

	tex_x = (int)((wall_x / BLOCK) * ray->texture->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= ray->texture->width)
		tex_x = ray->texture->width - 1;
	return (tex_x);
}

int	get_texture_y(int y, int start_y, int height, t_ray_info *ray)
{
	int	tex_y;

	tex_y = ((y - start_y) * ray->texture->height) / height;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= ray->texture->height)
		tex_y = ray->texture->height - 1;
	return (tex_y);
}
