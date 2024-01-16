
#include "../incl/cub3d.h"

int	all_keys_found(cub3d_t *cub3d, int i)
{
	key_node_t	*temp;

	temp = cub3d->level->key_groups[i].keys;
	while (temp != NULL)
	{
		if (temp->collected == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

static int	obstacle_found_dist(cub3d_t *cub3d, vector_t v_map_check, int dist)
{
	if (v_map_check.x >= 0
		&& v_map_check.x < cub3d->level->map_columns
		&& v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& (cub3d->level->map[v_map_check.y][v_map_check.x] == WALL
	))
		return (1);
	if (v_map_check.x >= 0 && v_map_check.x < cub3d->level->map_columns
		&& v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& (cub3d->level->map[v_map_check.y][v_map_check.x] == 'A'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'B'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'C'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'D'))
	{
		if (dist > 1)
			return (1);
		if (check_if_door_unlocked(cub3d, v_map_check.x, v_map_check.y))
			return (0);
		else
			return (1);
	}
	return (0);
}

int	wall_checker(int wall_flag, dvector_t end, dvector_t pos)
{
	if (wall_flag == 1 && end.x > pos.x)
		return (WE);
	else if (wall_flag == 1)
		return (EA);
	else if (wall_flag == 0 && pos.y < end.y)
		return (NO);
	else if (wall_flag == 0 && pos.y >= end.y)
		return (SO);
	else
		return (5);
}

int	find_end_point(cub3d_t *cub3d, player_t player, double radians, dvector_t end)
{
	dvector_t	v_ray_step_size;
	dvector_t	v_ray_1d_length;
	vector_t	v_map_check;
	vector_t	v_step;
	double		dist;

	v_ray_step_size = init_step_size(radians);
	v_map_check.x = (int)player.pos.x;
	v_map_check.y = (int)player.pos.y;
	v_step = init_v_step(radians * 180 / M_PI);
	v_ray_1d_length = init_len(player.pos, radians * 180 / M_PI, v_map_check, v_ray_step_size);
	dist = 0;
	while (1)
	{
		if (v_ray_1d_length.x < v_ray_1d_length.y)
		{
			v_map_check.x += v_step.x;
			dist = v_ray_1d_length.x;
			v_ray_1d_length.x += v_ray_step_size.x;
			if (obstacle_found_dist(cub3d, v_map_check, dist))
				return (wall_checker(1, end, player.pos));
		}
		else
		{
			v_map_check.y += v_step.y;
			dist = v_ray_1d_length.y;
			v_ray_1d_length.y += v_ray_step_size.y;
			if (obstacle_found_dist(cub3d, v_map_check, dist))
				return (wall_checker(0, end, player.pos));
		}
	}
}

dvector_t	init_step_size(double angle)
{
	dvector_t	v_ray_step_size;
	dvector_t	v_ray_dir;

	v_ray_dir.x = cos(angle);
	v_ray_dir.y = sin(angle);
	v_ray_step_size.x = sqrt(1 + (v_ray_dir.y / v_ray_dir.x) * (v_ray_dir.y
				/ v_ray_dir.x));
	v_ray_step_size.y = sqrt(1 + (v_ray_dir.x / v_ray_dir.y) * (v_ray_dir.x
				/ v_ray_dir.y));
	return (v_ray_step_size);
}
