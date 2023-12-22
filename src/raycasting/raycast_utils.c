
#include "../incl/cub3d.h"

dvector_t init_ray_1D_length(dvector_t start_pos, double dir, vector_t vMapCheck, dvector_t vRayUnitStepSize)
{
	dvector_t		vRayLength1D;
	dvector_t		vRayDir;

	vRayDir.x = cos(to_radians(dir));
	vRayDir.y = sin(to_radians(dir));
	if (vRayDir.x < 0)
		vRayLength1D.x = (start_pos.x - vMapCheck.x) * vRayUnitStepSize.x;
	else
		vRayLength1D.x = (vMapCheck.x + 1.0 - start_pos.x) * vRayUnitStepSize.x;
	if (vRayDir.y < 0)
		vRayLength1D.y = (start_pos.y - vMapCheck.y) * vRayUnitStepSize.y;
	else
		vRayLength1D.y = (vMapCheck.y + 1.0 - start_pos.y) * vRayUnitStepSize.y;
	return (vRayLength1D);
}

void	raycasting(cub3d_t *cub3d)
{
	double			fov_start;
	double			max_dist;
	unsigned int	i;

	fov_start = within_two_pi(cub3d->player.angle - to_radians((cub3d->fov
					/ 2)));
	i = 0;
	max_dist = sqrt(cub3d->img->width * cub3d->img->width + cub3d->img->height
			* cub3d->img->height);
	while (i < cub3d->img->width)
	{
		cub3d->rays[i].angle = within_two_pi(fov_start
				+ to_radians((cub3d->fov * i / cub3d->img->width)));
		raycast(cub3d, &cub3d->player, &cub3d->rays[i], max_dist);
		i++;
	}
}

vector_t	init_v_step(double dir)
{
	vector_t	v_step;
	dvector_t	v_ray_dir;

	v_ray_dir.x = cos(to_radians(dir));
	v_ray_dir.y = sin(to_radians(dir));
	if (v_ray_dir.x < 0)
		v_step.x = -1;
	else
		v_step.x = 1;
	if (v_ray_dir.y < 0)
		v_step.y = -1;
	else
		v_step.y = 1;
	return (v_step);
}

void	set_wall_direction(ray_t *ray, player_t *player, int wall_flag)
{
	if (wall_flag == X && player->pos.x < ray->end.x)
		ray->wall = WE;
	else if (wall_flag == X && ray->end.x < player->pos.x)
		ray->wall = EA;
	else if (wall_flag == Y && player->pos.y < ray->end.y)
		ray->wall = NO;
	else
		ray->wall = SO;
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
	while (ray->length < max_dist)
	{
		adjust(&vMapCheck, ray, vStep, &vRayLength1D);
		adjust_wall_flag(&vRayLength1D, vRayUnitStepSize, &wall_flag);
		if (obstacle_found(cub3d, vMapCheck, ray, ray->angle))
			break ;
	}
	if (ray->target == WALL)
		set_wall_direction(ray, player, wall_flag);
	else
		ray->wall = ray->target;
	return (SUCCESS);
}
