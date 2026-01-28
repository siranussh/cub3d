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

void draw_map(t_game *game)
{
	char **map = game->map;
	int color = 0x0000FF;
	int y;
	int x;

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

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
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
void init_game(t_game *game)
{
	init_player(&game->player);
	game->map = get_map();
    game->mlx = mlx_init();
    game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);//unlocks pixel-level access
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);//linux version
}

bool touch(float px, float py, t_game *game)
{
	int x;
	int y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

// void draw_line(t_player *player, t_game *game, float start_x)
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
// 		put_pixel(ray_x, ray_y, 0xFF0000, game);
// 		ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}
// 	float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
//     float height = (BLOCK / dist) * (WIDTH / 2);
//     int start_y = (HEIGHT - height) / 2;
//     int end = start_y + height; //each ray draws one vertical wall slice, close wall->short,
// }



int draw_loop(t_game *game)
{
	t_player *player;
	float fraction;
	float start_x;
	int i;

	player = &game->player;
	move_player(player);
	clear_image(game);
	draw_square(player->x, player->y, 10, 0x00FF00, game);
	draw_map(game);
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6; //PI 180 start_x = 30
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	return (0);
}

int main()
{
    t_game game;
    init_game(&game);
	mlx_hook(game.window, 2, 1L<<0, key_press, &game);//1L<<0 this is bitmask for key press
	mlx_hook(game.window, 3, 1L<<1, key_release, &game);//1L<<1 this is bitmask for key press
	
	// mlx_put_image_to_window(game.mlx, game.window, game.img, 0, 0);//macos version
	// draw_square(WIDTH / 2, HEIGHT / 2, 10, 0x00FF00, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);
}

