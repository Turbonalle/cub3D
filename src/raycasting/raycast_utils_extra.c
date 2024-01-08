
#include "../incl/cub3d.h"

static void	update_end(cub3d_t *cub3d, double dir, ray_t *ray)
{
	dvector_t	v_ray_dir;

	v_ray_dir.x = cos(dir);
	v_ray_dir.y = sin(dir);
	ray->end.x = cub3d->player.pos.x + v_ray_dir.x * ray->length;
	ray->end.y = cub3d->player.pos.y + v_ray_dir.y * ray->length;
}

static double	dist_to_door(dvector_t pos, ray_t *ray)
{
	dvector_t	v_ray_dir;
	dvector_t	help;
	double		dist;

	v_ray_dir.x = cos(ray->angle);
	v_ray_dir.y = sin(ray->angle);
	ray->end.x = pos.x + v_ray_dir.x * ray->length;
	if (1 - fmod(ray->end.x, 1) > 0.0001)
		help.x = 0.5 + floor(ray->end.x);
	else
		help.x = ray->end.x + 0.5;
	ray->end.y = pos.y + v_ray_dir.y * ray->length;
	if (1 - fmod(ray->end.y, 1) > 0.0001)
		help.y = 0.5 + floor(ray->end.y);
	else
		help.y = ray->end.y + 0.5;
	dist = dist_between_d_vectors(help, pos);
	return (dist);
}

static int	wall_found(cub3d_t *cub3d, vector_t v_map_check)
{
	return (v_map_check.x >= 0
		&& v_map_check.x < cub3d->level->map_columns
		&& v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& cub3d->level->map[v_map_check.y][v_map_check.x] == WALL);
}

static int	goal_found(cub3d_t *cub3d, vector_t v_map_check)
{
	return (v_map_check.x >= 0
		&& v_map_check.x < cub3d->level->map_columns
		&& v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& cub3d->level->map[v_map_check.y][v_map_check.x] == 'G');
}

static int	door_found(cub3d_t *cub3d, vector_t v_map_check, ray_t *ray)
{
	double	dist;

	if (v_map_check.x >= 0 && v_map_check.x
		< cub3d->level->map_columns && v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& (cub3d->level->map[v_map_check.y][v_map_check.x] == 'A'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'B'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'C'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'D'))
	{
		dist = dist_to_door(cub3d->player.pos, ray);
		if (dist > 4.0)
			return (1);
		if (check_if_door_open(cub3d, v_map_check.x, v_map_check.y))
			return (0);
		else
			return (1);
	}
	return (0);
}


int	obstacle_found(cub3d_t *cub3d, vector_t v_map_check, ray_t *ray, double dir)
{
	if (wall_found(cub3d, v_map_check))
	{
		ray->target = cub3d->level->map[v_map_check.y][v_map_check.x];
		update_end(cub3d, dir, ray);
		return (1);
	}
	if (goal_found(cub3d, v_map_check))
	{
		ray->target = cub3d->level->map[v_map_check.y][v_map_check.x];
		update_end(cub3d, dir, ray);
		return (1);
	}
	if (door_found(cub3d, v_map_check, ray))
	{
		ray->target = cub3d->level->map[v_map_check.y][v_map_check.x];
		update_end(cub3d, dir, ray);
		return (1);
	}
	return (0);
}
