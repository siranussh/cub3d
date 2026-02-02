#include "../includes/cub3d.h"


int	handle_destroy(t_game *game)
{
	free_game(game);
	exit (0);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free_map(game->map);
}

void	close_game(t_game *game)
{
	if (!game)
		exit(0);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free_map(game->map);
	exit(0);
}
