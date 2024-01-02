
#include "../incl/cub3d.h"

static void	update_end(cub3d_t *cub3d, double dir, ray_t *ray)
{
	dvector_t	v_ray_dir;

	v_ray_dir.x = cos(dir);
	v_ray_dir.y = sin(dir);
	ray->end.x = cub3d->player.pos.x + v_ray_dir.x * ray->length;
	ray->end.y = cub3d->player.pos.y + v_ray_dir.y * ray->length;
}

void	adjust(vector_t *v_map_check, ray_t *ray, vector_t v_step, dvector_t *v_ray_1d_length)
{
	if (v_ray_1d_length->x < v_ray_1d_length->y)
	{
		v_map_check->x += v_step.x;
		ray->length = v_ray_1d_length->x;
	}
	else
	{
		v_map_check->y += v_step.y;
		ray->length = v_ray_1d_length->y;
	}
}

void	adjust_wall_flag(dvector_t *v_ray_1d_length, dvector_t v_ray_step_size, int *wall_flag)
{
	if (v_ray_1d_length->x < v_ray_1d_length->y)
	{
		v_ray_1d_length->x += v_ray_step_size.x;
		*wall_flag = X;
	}
	else
	{
		v_ray_1d_length->y += v_ray_step_size.y;
		*wall_flag = Y;
	}
}

void	adjust_no_flag(dvector_t *v_ray_1d_length, dvector_t v_ray_step_size)
{
	if (v_ray_1d_length->x < v_ray_1d_length->y)
		v_ray_1d_length->x += v_ray_step_size.x;
	else
		v_ray_1d_length->y += v_ray_step_size.y;
}

ray_t *cast_ray(cub3d_t *cub3d, ray_t *ray)
{
	dvector_t	v_ray_step_size;
	dvector_t	v_ray_1d_length;
	vector_t	v_map_check;
	vector_t	v_step;

	v_ray_step_size = init_step_size(cub3d->player.angle);
	v_map_check.x = (int)cub3d->player.pos.x;
	v_map_check.y = (int)cub3d->player.pos.y;
	v_step = init_v_step(ray->angle * 180 / M_PI);
	v_ray_1d_length = init_ray_1D_length(cub3d->player.pos,
			cub3d->player.angle * 180 / M_PI, v_map_check, v_ray_step_size);
	while (ray->length < DISTRACTION_THROW_DISTANCE)
	{
		adjust(&v_map_check, ray, v_step, &v_ray_1d_length);
		adjust_no_flag(&v_ray_1d_length, v_ray_step_size);
		if (obstacle_found(cub3d, v_map_check, ray, cub3d->player.angle))
			break ;
	}
	update_end(cub3d, cub3d->player.angle, ray);
	return (ray);
}
