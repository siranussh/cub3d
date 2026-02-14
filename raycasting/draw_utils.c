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
