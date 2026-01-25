#ifndef RAYCASTING_H
#define RAYCASTING_H



# include "libft.h"
# include <unistd.h> // close() read()
# include <stdlib.h> // open() malloc() exit()
# include <fcntl.h> // open() flags
# include <stdio.h> // perror()
# include <string.h> // strerror()
#include <sys/time.h> // gettimeofday()
#include <stdbool.h>
#include <math.h>
#include "mlx.h"

//linux
// # define W 119
// # define A 97
// # define S 115
// # define D 100

//macos
# define W 13
# define A 0
# define S 1
# define D 2

# define PI 3.14159265359 //for angle calculations

typedef struct s_player
{
    float x;
    float y;
    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
} t_player;

typedef struct s_game
{
    void *mlx;
    void *window;
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
    t_player player;
} t_game;

# define WIDTH 1280
# define HEIGHT 720

void    print_error(char *str);

//player.c
void    init_player(t_player *player);
int     key_press(int keycode, t_player *player);
int     key_release(int keycode , t_player *player);
void    move_player(t_player *player);

//raycasting.c
void put_pixel(int x, int y, int color, t_game *game);
void  clear_image(t_game *game);
void draw_square(int x, int y, int size, int color, t_game *game);
void init_game(t_game *game);
int draw_loop(t_game *game);

#endif 