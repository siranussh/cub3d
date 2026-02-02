#include "../includes/cub3d.h"

static void move_forward_backward(t_player *player, float *move_x, float *move_y)
{
    float cos_angle;
    float sin_angle;

    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);
    if (player->key_up)
    {
        *move_x += cos_angle;
        *move_y += sin_angle;
    }
    if (player->key_down)
    {
        *move_x -= cos_angle;
        *move_y -= sin_angle;
    }
}

static void move_strafe(t_player *player, float *move_x, float *move_y)
{
    float cos_angle;
    float sin_angle;

    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);
    if (player->key_left)
    {
        *move_x += sin_angle;
        *move_y -= cos_angle;
    }
    if (player->key_right)
    {
        *move_x -= sin_angle;
        *move_y += cos_angle;
    }
}

static void normalize_vector(float *x, float *y)
{
    float len;
    
    len = sqrt((*x) * (*x) + (*y) * (*y));
    if (len > 0)
    {
        *x /= len;
        *y /= len;
    }
}

static void get_movement_vector(t_player *player, float *move_x, float *move_y)
{
    *move_x = 0;
    *move_y = 0;

    move_forward_backward(player, move_x, move_y);
    move_strafe(player, move_x, move_y);
    normalize_vector(move_x, move_y);
}

void update_player_position(t_player *player, int speed, t_game *game)
{
    float move_x;
    float move_y;
    float new_x;
    float new_y;

    get_movement_vector(player, &move_x, &move_y);

    new_x = player->x + move_x * speed;
    new_y = player->y + move_y * speed;

    if (!touch(new_x, player->y, game))
        player->x = new_x;
    if (!touch(player->x, new_y, game))
        player->y = new_y;
}
