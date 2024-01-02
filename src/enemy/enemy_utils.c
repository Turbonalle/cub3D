
#include "../incl/cub3d.h"

int	check_if_door_open(cub3d_t *cub3d, int xcoord, int ycoord)
{
	char	index;

	index = cub3d->level->map[ycoord][xcoord];
	if (all_keys_found(cub3d, index - 'A'))
		return (1);
	return (0);
}

int	wall_or_door_found(cub3d_t *cub3d, vector_t v_map_check)
{
	if (v_map_check.x >= 0
		&& v_map_check.x < cub3d->level->map_columns
		&& v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& cub3d->level->map[v_map_check.y][v_map_check.x] == WALL)
		return (1);
	if (v_map_check.x >= 0
		&& v_map_check.x < cub3d->level->map_columns && v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& (cub3d->level->map[v_map_check.y][v_map_check.x] == 'A'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'B'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'C'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'D'))
	{
		if (dist_between(v_map_check, cub3d->player.pos) > 4)
			return (1);
		if (check_if_door_open(cub3d, v_map_check.x, v_map_check.y))
			return (0);
		else
			return (1);
	}
	return (0);
}

static int	ray_to_distraction(cub3d_t *cub3d, double dir_to_distraction, int i)
{
	dvector_t		v_ray_step_size;
	dvector_t		v_ray_1d_length;
	double			max_dist;
	vector_t		v_map_check;
	vector_t		v_step;
	ray_t			*ray;

	max_dist = sqrt(pow(cub3d->player.pos.x - cub3d->level->distractions[i].pos.x, 2) + pow(cub3d->player.pos.y - cub3d->level->distractions[i].pos.y, 2));
	v_map_check.x = (int)cub3d->player.pos.x;
	v_map_check.y = (int)cub3d->player.pos.y;
	v_ray_step_size = init_step_size(to_radians(dir_to_distraction));
	v_step = init_v_step(dir_to_distraction);
	v_ray_1d_length = init_ray_1D_length(cub3d->player.pos, dir_to_distraction, v_map_check, v_ray_step_size);
	ray = init_ray_dir(dir_to_distraction);
	if (!ray)
		return (0);
	while (ray->length < max_dist)
	{
		if (wall_or_door_found(cub3d, v_map_check))
			return (free(ray), 0);
		adjust(&v_map_check, ray, v_step, &v_ray_1d_length);
		adjust_no_flag(&v_ray_1d_length, v_ray_step_size);
	}
	free(ray);
	return (1);
}

void	see_distraction(cub3d_t *cub3d, double dir_to_distraction, int i)
{
	double	angle_min;
	double	angle_max;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	cub3d->level->distractions[i].visible = FALSE;
	if (angle_max < angle_min)
	{
		if (cub3d->fov < 360 && dir_to_distraction > angle_max && dir_to_distraction < angle_min)
			return ;
		else if (!ray_to_distraction(cub3d, dir_to_distraction, i))
			return ;
	}
	else
	{
		if (cub3d->fov < 360 && (dir_to_distraction < angle_min || dir_to_distraction > angle_max))
			return ;
		else if (!ray_to_distraction(cub3d, dir_to_distraction, i))
			return ;
	}
	cub3d->level->distractions[i].visible = TRUE;
	draw_distraction(cub3d, dir_to_distraction, i);
	return ;
}

