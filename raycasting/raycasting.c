
#include "raycasting.h"


void put_pixel(int x, int y, int color, t_game *game)
{
	int index;
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;
	index = y * game->size_line + x * game->bpp / 8;//in which position in memory is the pixel(x, y) we convert 2d(x,y) -> to 1D index
	game->data[index] = color & 0xFF;//blue
	game->data[index + 1] = (color >> 8) & 0xFF;//green
	game->data[index + 2] = (color >> 16) & 0xFF;//red  this just writes the color bytes into memory
}

void  clear_image(t_game *game)
{
	int y;
	int x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}
//to draw pixels/squares in an MLX image
void draw_square(int x, int y, int size, int color, t_game *game)
{
	int i;
	
	i = -1;
	while (++i < size)
		put_pixel(x + i, y, color, game);
	i = -1;
	while(++i < size)
		put_pixel(x, y + i, color, game);
	i = -1;
	while (++i < size)
		put_pixel(x +  size, y + i, color, game);
	i = -1;
	while (++i < size)
		put_pixel(x + i, y + size, color, game);
}

//creating window for game with size we prefer
/*ray is a imaginary straight line goinf=g in a specific direction until it hits a wall*/
//raycasting is throwing many rays ...🦗
//game->data is a 1D array of bytes
void init_game(t_game *game)
{
	init_player(&game->player);
    game->mlx = mlx_init();
    game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);//unlocks pixel-level access
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);//linux version
}

int draw_loop(t_game *game)
{
	t_player *player;
	
	player = &game->player;
	// clear_image(game);///this one or bzero
	// ft_bzero(game->data, HEIGHT * game->size_line);///
	move_player(player);
	draw_square(player->x, player->y, 5, 0x00FF00, game);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	return (0);
}

int main()
{
    t_game game;
    init_game(&game);
	mlx_hook(game.window, 2, 1L<<0, key_press, &game);//1L<<0 this is bitmask for key press
	mlx_hook(game.window, 3, 1L<<1, key_release, &game);//1L<<1 this is bitmask for key press
	// draw_square(WIDTH / 2, HEIGHT / 2, 10, 0x00FF00, &game);
	// mlx_put_image_to_window(game.mlx, game.window, game.img, 0, 0);//macos version
	mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);
}

