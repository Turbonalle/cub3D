
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

dvector_t	init_ray_step_size(double dir)
{
	dvector_t		vRayDir;
	dvector_t		vRayUnitStepSize;

	vRayDir.x = cos(to_radians(dir));
	vRayDir.y = sin(to_radians(dir));
	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x));
	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y));
	return (vRayUnitStepSize);
}

int	enemy_ray_to_distraction(cub3d_t *cub3d, dvector_t distraction, double dir_to, int i)
{
	dvector_t		vRayUnitStepSize;
	dvector_t		vRayLength1D;
	vector_t		vMapCheck;
	ray_t			*ray;
	double			max_dist;

	max_dist = dist_between_d_vectors(distraction, cub3d->enemy[i].pos);
	vMapCheck.x = (int)cub3d->enemy[i].pos.x;
	vMapCheck.y = (int)cub3d->enemy[i].pos.y;
	vRayUnitStepSize = init_ray_step_size(dir_to);
	vRayLength1D = init_ray_1D_length(cub3d->enemy[i].pos, dir_to, vMapCheck, vRayUnitStepSize);
	ray = init_ray(cub3d->enemy, i);
	if (!ray)
		return (0);
	ray->angle = dir_to;
	while (ray->length < max_dist)
	{
		if (wall_or_door_found(cub3d, vMapCheck))
			return (free(ray), 0);
		adjust(&vMapCheck, ray, init_v_step(dir_to), &vRayLength1D);
		adjust_no_flag(&vRayLength1D, vRayUnitStepSize);
	}
	cub3d->enemy[i].angle = to_radians(ray->angle);
	cub3d->enemy[i].target = cub3d->level->distraction;
	return (free(ray), 1);
}

int	ray_to_enemy(cub3d_t *cub3d, double dir_to_enemy, double max_dist)
{
	dvector_t		vRayUnitStepSize;
	dvector_t		vRayLength1D;
	vector_t		vMapCheck;
	vector_t		vStep;
	ray_t			*ray;

	vMapCheck.x = (int)cub3d->player.pos.x;
	vMapCheck.y = (int)cub3d->player.pos.y;
	vRayUnitStepSize = init_step_size(to_radians(dir_to_enemy));
	vStep = init_v_step(dir_to_enemy);
	vRayLength1D = init_ray_1D_length(cub3d->player.pos, dir_to_enemy, vMapCheck, vRayUnitStepSize);
	ray = init_ray_dir(dir_to_enemy);
	if (!ray)
		return (0);
	while (ray->length < max_dist)
	{
		if (wall_or_door_found(cub3d, vMapCheck))
			return (free(ray), 0);
		adjust(&vMapCheck, ray, vStep, &vRayLength1D);
		adjust_no_flag(&vRayLength1D, vRayUnitStepSize);
	}
	free(ray);
	return (1);
}
