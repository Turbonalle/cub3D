
#include "../incl/cub3d.h"

static void	update_end(cub3d_t *cub3d, double dir, ray_t *ray)
{
	dvector_t	vRayDir;

	vRayDir.x = cos(dir);
	vRayDir.y = sin(dir);
	ray->end.x = cub3d->player.pos.x + vRayDir.x * ray->length;
	ray->end.y = cub3d->player.pos.y + vRayDir.y * ray->length;
}

static dvector_t init_step_size(double angle)
{
	dvector_t	vRayUnitStepSize;
	dvector_t	vRayDir;

	vRayDir.x = cos(angle);
	vRayDir.y = sin(angle);
	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y
				/ vRayDir.x));
	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x
				/ vRayDir.y));
	return (vRayUnitStepSize);
}

int	raycast(cub3d_t *cub3d, player_t *player, ray_t *ray, double max_dist)
{
	dvector_t	vRayUnitStepSize;
	dvector_t	vRayLength1D;
	vector_t	vMapCheck;
	vector_t	vStep;
	int			wall_flag;

	vRayUnitStepSize = init_step_size(ray->angle);
	vMapCheck.x = (int)player->pos.x;
	vMapCheck.y = (int)player->pos.y;
	vStep = init_v_step(ray->angle * 180 / M_PI);
	vRayLength1D = init_ray_1D_length(cub3d->player.pos, ray->angle * 180 / M_PI, vMapCheck, vRayUnitStepSize);
	wall_flag = 0;
	while (ray->length < max_dist)
	{
		if (vRayLength1D.x < vRayLength1D.y)
		{
			vMapCheck.x += vStep.x;
			ray->length = vRayLength1D.x;
			vRayLength1D.x += vRayUnitStepSize.x;
			wall_flag = X;
		}
		else
		{
			vMapCheck.y += vStep.y;
			ray->length = vRayLength1D.y;
			vRayLength1D.y += vRayUnitStepSize.y;
			wall_flag = Y;
		}
		if (obstacle_found(cub3d, vMapCheck, ray))
		{
			ray->target = cub3d->level->map[vMapCheck.y][vMapCheck.x];
			update_end(cub3d, ray->angle, ray);
			break ;
		}
	}
	if (ray->target == WALL)
		set_wall_direction(ray, player, wall_flag);
	else
		ray->wall = ray->target;
	return (SUCCESS);
}

ray_t *cast_ray(cub3d_t *cub3d, ray_t *ray)
{
	dvector_t	vRayUnitStepSize;
	dvector_t	vRayLength1D;
	vector_t	vMapCheck;
	vector_t	vStep;
	double		max_dist;

	vRayUnitStepSize = init_step_size(cub3d->player.angle);
	vMapCheck.x = (int)cub3d->player.pos.x;
	vMapCheck.y = (int)cub3d->player.pos.y;
	vStep = init_v_step(ray->angle * 180 / M_PI);
	vRayLength1D = init_ray_1D_length(cub3d->player.pos, cub3d->player.angle * 180 / M_PI, vMapCheck, vRayUnitStepSize);
	max_dist = DISTRACTION_THROW_DISTANCE;
	while (ray->length < max_dist)
	{
		if (vRayLength1D.x < vRayLength1D.y)
		{
			vMapCheck.x += vStep.x;
			ray->length = vRayLength1D.x;
			vRayLength1D.x += vRayUnitStepSize.x;
		}
		else
		{
			vMapCheck.y += vStep.y;
			ray->length = vRayLength1D.y;
			vRayLength1D.y += vRayUnitStepSize.y;
		}
		if (obstacle_found(cub3d, vMapCheck, ray))
		{
			ray->target = cub3d->level->map[vMapCheck.y][vMapCheck.x];
			update_end(cub3d, cub3d->player.angle, ray);
			break ;
		}
	}
	update_end(cub3d, cub3d->player.angle, ray);
	printf("ray ends at %f,%f\n",ray->end.x,ray->end.y);
	return (ray);
}
