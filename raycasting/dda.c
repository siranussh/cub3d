#include "../includes/cub3d.h"


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