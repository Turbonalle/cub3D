
#include "../incl/cub3d.h"

static ray_t	*init_ray(t_enemy *enemy, int i)
{
	ray_t	*ray;

	ray = malloc(sizeof(ray_t));
	if (!ray)
		return (NULL);
	ray->angle = enemy[i].dir_player;
	ray->length = 0;
	ray->target = 0;
	ray->wall = 0;
	ray->end.x = 0;
	ray->end.y = 0;
	return (ray);
}

static int	wall_or_door_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	if (vMapCheck.x >= 0
		&& vMapCheck.x < cub3d->level->map_columns
		&& vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->level->map_rows
		&& cub3d->level->map[vMapCheck.y][vMapCheck.x] == WALL)
		return (1);
	if (vMapCheck.x >= 0 && vMapCheck.x
		< cub3d->level->map_columns && vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->level->map_rows
		&& (cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'A'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'B'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'C'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'D'))
	{
		if (dist_between(vMapCheck, cub3d->player.pos) > 3)
			return (1);
		if (check_if_door_open(cub3d, vMapCheck.x, vMapCheck.y))
			return (0);
		else
			return (1);
	}
	return (0);
}

dvector_t init_ray_step_size(double dir)
{
	dvector_t		vRayDir;
	dvector_t		vRayUnitStepSize;

	vRayDir.x = cos(to_radians(dir));
	vRayDir.y = sin(to_radians(dir));
	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x));
	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y));
	return (vRayUnitStepSize);
}

int	enemy_ray_to_distraction(cub3d_t *cub3d, dvector_t distraction, double dir_to_distraction, int i)
{
	dvector_t		vRayUnitStepSize;
	dvector_t		vRayLength1D;
	vector_t		vMapCheck;
	vector_t		vStep;
	ray_t			*ray;
	double			max_dist;

	max_dist = dist_between_d_vectors(distraction, cub3d->enemy[i].pos);
	vMapCheck.x = (int)cub3d->enemy[i].pos.x;
	vMapCheck.y = (int)cub3d->enemy[i].pos.y;
	vStep = init_v_step(dir_to_distraction);
	vRayUnitStepSize = init_ray_step_size(dir_to_distraction);
	vRayLength1D = init_ray_1D_length(cub3d->enemy[i].pos, dir_to_distraction, vMapCheck, vRayUnitStepSize);
	ray = init_ray(cub3d->enemy, i);
	if (!ray)
		return (0);
	ray->angle = dir_to_distraction;
	while (ray->length < max_dist)
	{
		if (wall_or_door_found(cub3d, vMapCheck))
		{
			free(ray);
			return (0);
		}
		adjust(&vMapCheck, ray, vStep, &vRayLength1D);
		adjust_no_flag(&vRayLength1D, vRayUnitStepSize);
	}
	cub3d->enemy[i].angle = to_radians(ray->angle);
	cub3d->enemy[i].target = cub3d->level->distraction;
	free(ray);
	return (1);
}
