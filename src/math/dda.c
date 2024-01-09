
#include "../incl/cub3d.h"

int all_keys_found(cub3d_t *cub3d, int i)
{
	key_node_t *temp;
	temp = cub3d->level->key_groups[i].keys;
	while (temp != NULL)
	{
		if (temp->collected == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

static int	wall_or_door_found_dist(cub3d_t *cub3d, vector_t v_map_check, int dist)
{
	if	(v_map_check.x >= 0
			&& v_map_check.x < cub3d->level->map_columns
			&& v_map_check.y >= 0
			&& v_map_check.y < cub3d->level->map_rows
			&& (cub3d->level->map[v_map_check.y][v_map_check.x] == WALL
			))
		return (1);
	if (v_map_check.x >= 0 && v_map_check.x < cub3d->level->map_columns && v_map_check.y >= 0
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

 //-----------------------------------------------------------------------------

static void update_end(cub3d_t *cub3d, dvector_t *v_ray_dir, dvector_t end, double *dist, int *end_found)
{
	(void)end;
	end.x = cub3d->minimap.player_pos.x + (*v_ray_dir).x * *dist * cub3d->minimap.tile_size;
	end.y = cub3d->minimap.player_pos.y + (*v_ray_dir).y * *dist * cub3d->minimap.tile_size;
	*end_found = TRUE;
}

//------------------------------------------------------------------------------

int find_end_point(cub3d_t *cub3d, player_t player, double radians, dvector_t end)
{
	dvector_t v_ray_step_size;
	dvector_t v_ray_1d_length;
	dvector_t v_ray_dir;
	vector_t v_map_check;
	vector_t v_step;
	int end_found = FALSE;

	v_ray_dir.x = cos(radians);
	v_ray_dir.y = sin(radians);

	v_ray_step_size = init_step_size(radians);

	v_map_check.x = (int)player.pos.x;
	v_map_check.y = (int)player.pos.y;

	v_step = init_v_step(radians * 180 / M_PI);
	v_ray_1d_length = init_ray_1D_length(player.pos, radians * 180 / M_PI, v_map_check, v_ray_step_size);

	double dist = 0;
	double max_dist = sqrt(cub3d->img->width * cub3d->img->width + cub3d->img->height * cub3d->img->height);
	int wall_flag = 0;
	while (!end_found && dist < max_dist)
	{
		if (v_ray_1d_length.x < v_ray_1d_length.y)
		{
			v_map_check.x += v_step.x;
			dist = v_ray_1d_length.x;
			v_ray_1d_length.x += v_ray_step_size.x;
			wall_flag = 1;
		}
		else
		{
			v_map_check.y += v_step.y;
			dist = v_ray_1d_length.y;
			v_ray_1d_length.y += v_ray_step_size.y;
			wall_flag = 0;
		}
		if (wall_or_door_found_dist(cub3d, v_map_check, dist))
			update_end(cub3d, &v_ray_dir, end, &dist, &end_found);
	}
	if (wall_flag == 1 && end.x > player.pos.x)
		return (WE);
	else if (wall_flag == 1)
		return (EA);
	else if (wall_flag == 0 && player.pos.y < end.y)
		return (NO);
	else
		return (SO);
}

dvector_t init_step_size(double angle)
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
