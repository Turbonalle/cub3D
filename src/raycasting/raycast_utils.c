
#include "../incl/cub3d.h"

dvector_t init_ray_1D_length(dvector_t start_pos, double dir, vector_t v_map_check, dvector_t v_ray_step_size)
{
	dvector_t		v_ray_1d_length;
	dvector_t		v_ray_dir;

	v_ray_dir.x = cos(to_radians(dir));
	v_ray_dir.y = sin(to_radians(dir));
	if (v_ray_dir.x < 0)
		v_ray_1d_length.x = (start_pos.x - v_map_check.x) * v_ray_step_size.x;
	else
		v_ray_1d_length.x = (v_map_check.x + 1.0 - start_pos.x) * v_ray_step_size.x;
	if (v_ray_dir.y < 0)
		v_ray_1d_length.y = (start_pos.y - v_map_check.y) * v_ray_step_size.y;
	else
		v_ray_1d_length.y = (v_map_check.y + 1.0 - start_pos.y) * v_ray_step_size.y;
	return (v_ray_1d_length);
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
	dvector_t	v_ray_step_size;
	dvector_t	v_ray_1d_length;
	vector_t	v_map_check;
	vector_t	v_step;
	int			wall_flag;

	v_ray_step_size = init_step_size(ray->angle);
	v_map_check.x = (int)player->pos.x;
	v_map_check.y = (int)player->pos.y;
	v_step = init_v_step(ray->angle * 180 / M_PI);
	v_ray_1d_length = init_ray_1D_length(cub3d->player.pos, ray->angle * 180 / M_PI, v_map_check, v_ray_step_size);
	while (ray->length < max_dist)
	{
		adjust(&v_map_check, ray, v_step, &v_ray_1d_length);
		adjust_wall_flag(&v_ray_1d_length, v_ray_step_size, &wall_flag);
		if (obstacle_found(cub3d, v_map_check, ray, ray->angle))
			break ;
	}
	if (ray->target == WALL)
		set_wall_direction(ray, player, wall_flag);
	else
		ray->wall = ray->target;
	return (SUCCESS);
}
