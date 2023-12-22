
#include "../incl/cub3d.h"

static void	update_end(cub3d_t *cub3d, double dir, ray_t *ray)
{
	dvector_t	vRayDir;

	vRayDir.x = cos(dir);
	vRayDir.y = sin(dir);
	ray->end.x = cub3d->player.pos.x + vRayDir.x * ray->length;
	ray->end.y = cub3d->player.pos.y + vRayDir.y * ray->length;
}

void	adjust(vector_t *vMapCheck, ray_t *ray, vector_t vStep, dvector_t *vRayLength1D)
{
	if (vRayLength1D->x < vRayLength1D->y)
	{
		vMapCheck->x += vStep.x;
		ray->length = vRayLength1D->x;
	}
	else
	{
		vMapCheck->y += vStep.y;
		ray->length = vRayLength1D->y;
	}
}

void	adjust_wall_flag(dvector_t *vRayLength1D, dvector_t vRayUnitStepSize, int *wall_flag)
{
	if (vRayLength1D->x < vRayLength1D->y)
	{
		vRayLength1D->x += vRayUnitStepSize.x;
		*wall_flag = X;
	}
	else
	{
		vRayLength1D->y += vRayUnitStepSize.y;
		*wall_flag = Y;
	}
}

void	adjust_no_flag(dvector_t *vRayLength1D, dvector_t vRayUnitStepSize)
{
	if (vRayLength1D->x < vRayLength1D->y)
		vRayLength1D->x += vRayUnitStepSize.x;
	else
		vRayLength1D->y += vRayUnitStepSize.y;
}

ray_t *cast_ray(cub3d_t *cub3d, ray_t *ray)
{
	dvector_t	vRayUnitStepSize;
	dvector_t	vRayLength1D;
	vector_t	vMapCheck;
	vector_t	vStep;

	vRayUnitStepSize = init_step_size(cub3d->player.angle);
	vMapCheck.x = (int)cub3d->player.pos.x;
	vMapCheck.y = (int)cub3d->player.pos.y;
	vStep = init_v_step(ray->angle * 180 / M_PI);
	vRayLength1D = init_ray_1D_length(cub3d->player.pos,
			cub3d->player.angle * 180 / M_PI, vMapCheck, vRayUnitStepSize);
	while (ray->length < DISTRACTION_THROW_DISTANCE)
	{
		adjust(&vMapCheck, ray, vStep, &vRayLength1D);
		adjust_no_flag(&vRayLength1D, vRayUnitStepSize);
		if (obstacle_found(cub3d, vMapCheck, ray, cub3d->player.angle))
			break ;
	}
	update_end(cub3d, cub3d->player.angle, ray);
	return (ray);
}
