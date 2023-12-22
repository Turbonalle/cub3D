
#include "../incl/cub3d.h"

static void	update_end(cub3d_t *cub3d, double dir, ray_t *ray)
{
	dvector_t	vRayDir;

	vRayDir.x = cos(dir);
	vRayDir.y = sin(dir);
	ray->end.x = cub3d->player.pos.x + vRayDir.x * ray->length;
	ray->end.y = cub3d->player.pos.y + vRayDir.y * ray->length;
}

static int	wall_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	return (vMapCheck.x >= 0
		&& vMapCheck.x < cub3d->level->map_columns
		&& vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->level->map_rows
		&& cub3d->level->map[vMapCheck.y][vMapCheck.x] == WALL);
}

static int	goal_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	return (vMapCheck.x >= 0
		&& vMapCheck.x < cub3d->level->map_columns
		&& vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->level->map_rows
		&& cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'G');
}

static int	door_found(cub3d_t *cub3d, vector_t vMapCheck, ray_t *ray)
{
	if (vMapCheck.x >= 0 && vMapCheck.x
		< cub3d->level->map_columns && vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->level->map_rows
		&& (cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'A'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'B'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'C'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'D'))
	{
		if (ray->length > 3)
			return (1);
		if (check_if_door_open(cub3d, vMapCheck.x, vMapCheck.y))
			return (0);
		else
			return (1);
	}
	return (0);
}

int	obstacle_found(cub3d_t *cub3d, vector_t vMapCheck, ray_t *ray, double dir)
{
	if (wall_found(cub3d, vMapCheck))
	{
		ray->target = cub3d->level->map[vMapCheck.y][vMapCheck.x];
		update_end(cub3d, dir, ray);
		return (1);
	}
	if (goal_found(cub3d, vMapCheck))
	{
		ray->target = cub3d->level->map[vMapCheck.y][vMapCheck.x];
		update_end(cub3d, dir, ray);
		return (1);
	}
	if (door_found(cub3d, vMapCheck, ray))
	{
		ray->target = cub3d->level->map[vMapCheck.y][vMapCheck.x];
		update_end(cub3d, dir, ray);
		return (1);
	}
	return (0);
}
