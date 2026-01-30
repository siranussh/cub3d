#include "raycasting.h"


int	handle_destroy(t_game *game)
{
	close_game(game);
	return (0);
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
        free(game->map);//es pahin senc
	//free Ani's structures here

	exit(0);
}
