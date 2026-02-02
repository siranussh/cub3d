#include "raycasting.h"

void init_player(t_player *player)
{
    player->x = WIDTH / 2;
    player->y = HEIGHT / 2;
    player->angle = PI /2;
    player->key_up = false;
    player->key_left = false;
    player->key_right = false;
    player->key_down= false;
    player->left_rotate = false;
    player->right_rotate = false;
}


int key_press(int keycode, t_game *game)
{
    if (keycode == CLOSE)
		close_game(game);
    if(keycode == W)
        game->player.key_up = true;
    if(keycode == S)
        game->player.key_down = true;
    if(keycode == A)
        game->player.key_left = true;
    if(keycode == D)
        game->player.key_right = true;
    if (keycode == LEFT)
        game->player.left_rotate = true;
    if (keycode == RIGHT)
        game->player.right_rotate = true; 
    return (0);
}


int key_release(int keycode, t_game *game)
{
    if(keycode == W)
        game->player.key_up = false;
    if(keycode == S)
        game->player.key_down = false;
    if(keycode == A)
        game->player.key_left = false;
    if(keycode == D)
        game->player.key_right = false;
    if (keycode == LEFT)
        game->player.left_rotate = false;
    if (keycode == RIGHT)
        game->player.right_rotate = false; 
    return (0);
}

// void move_player(t_player *player)
// {
// 	int speed;
//     float angle_speed;
//     float cos_angle;
//     float sin_angle;

//     cos_angle= cos(player->angle);
//     sin_angle = sin(player->angle);
// 	speed = 5;
//     angle_speed = 0.1;

//     if(player->left_rotate)
//         player->angle -= angle_speed;
//     if (player->right_rotate)
//         player->angle += angle_speed;
//     if (player->angle > 2 * PI) //when angle goes too big you completed a full circle,wrap back to start
//         player->angle = 0;
//     if (player->angle < 0)//wrap to the end of the circle PI-half circle and 2 * PI ->full circle
//         player->angle = 2 * PI;

//     if (player->key_up)
//     {
//         player->x += cos_angle * speed;
//         player->y += sin_angle * speed;
//     }
//     if (player->key_down)
//     {
//         player->x -= cos_angle * speed;
//         player->y -= sin_angle * speed;
//     }
//     if (player->key_left)
//     {
//         player->x += sin_angle * speed;
//         player->y -= cos_angle * speed;
//     }
//     if (player->key_right)
//     {
//         player->x -= sin_angle * speed;
//         player->y += cos_angle * speed;
//     }
// }

void normalize_angle(float *angle)
{
    while (*angle < 0)
        *angle += 2 * PI;
    while (*angle >= 2 * PI)
        *angle -= 2 * PI;
}  

void update_player_rotation(t_player *player, float angle_speed)
{
    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;

    normalize_angle(&player->angle);
}

// void update_player_position(t_player *player, int speed, t_game *game)
// {
//     float cos_angle;
//     float sin_angle;
//     float move_x;
//     float move_y;
//     float len;
//     float new_x;
//     float new_y;

//     cos_angle = cos(player->angle);
//     sin_angle = sin(player->angle);
//     move_x = 0;
//     move_y = 0;
//     if (player->key_up)
//     {
//         move_x += cos_angle;
//         move_y += sin_angle;
//     }
//     if (player->key_down)
//     {
//         move_x -= cos_angle;
//         move_y -= sin_angle;
//     }
//     if (player->key_left)
//     {
//         move_x += sin_angle;
//         move_y -= cos_angle;
//     }
//     if (player->key_right)
//     {
//         move_x -= sin_angle;
//         move_y += cos_angle;
//     }
//     len = sqrt(move_x * move_x + move_y * move_y);
//     if (len > 0)
//     {
//         move_x /= len;
//         move_y /= len;
//     }
//     new_x = player->x + move_x * speed;
//     new_y = player->y + move_y * speed;

//     if (!touch(new_x, player->y, game))
//         player->x = new_x;
//     if (!touch(player->x, new_y, game))
//         player->y = new_y;
// }



void move_player(t_player *player, t_game *game)
{
    int speed;
    float angle_speed;

    speed = 3;
    angle_speed = 0.03f;

    update_player_rotation(player, angle_speed);
    update_player_position(player, speed, game);
}
