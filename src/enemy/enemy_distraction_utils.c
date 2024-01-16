/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_distraction_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:44:53 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 23:45:27 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ray->door_dir = 0;
	ray->end.x = 0;
	ray->end.y = 0;
	return (ray);
}

dvector_t	init_ray_step_size(double dir)
{
	dvector_t		v_ray_dir;
	dvector_t		v_ray_step_size;

	v_ray_dir.x = cos(to_radians(dir));
	v_ray_dir.y = sin(to_radians(dir));
	v_ray_step_size.x = sqrt(1 + (v_ray_dir.y / v_ray_dir.x)
			* (v_ray_dir.y / v_ray_dir.x));
	v_ray_step_size.y = sqrt(1 + (v_ray_dir.x / v_ray_dir.y)
			* (v_ray_dir.x / v_ray_dir.y));
	return (v_ray_step_size);
}

int	enemy_ray_to_distraction(cub3d_t *cub3d, dvector_t distraction,
		double dir_to, int i)
{
	dvector_t		step;
	dvector_t		v_ray_1d_length;
	vector_t		v_map_check;
	ray_t			*ray;
	double			max_dist;

	max_dist = dist_between_d_vectors(distraction, cub3d->enemy[i].pos);
	v_map_check.x = (int)cub3d->enemy[i].pos.x;
	v_map_check.y = (int)cub3d->enemy[i].pos.y;
	step = init_ray_step_size(dir_to);
	v_ray_1d_length = init_len(cub3d->enemy[i].pos, dir_to, v_map_check, step);
	ray = init_ray(cub3d->enemy, i);
	if (!ray)
		return (0);
	ray->angle = dir_to;
	while (ray->length < max_dist)
	{
		if (wall_or_door_found(cub3d, v_map_check))
			return (free(ray), 0);
		adjust(&v_map_check, ray, init_v_step(dir_to), &v_ray_1d_length);
		adjust_no_flag(&v_ray_1d_length, step);
	}
	cub3d->enemy[i].angle = to_radians(ray->angle);
	cub3d->enemy[i].target = cub3d->level->distraction;
	return (free(ray), 1);
}

int	ray_to_enemy(cub3d_t *cub3d, double dir_to_enemy, double max_dist)
{
	dvector_t		v_ray_step_size;
	dvector_t		v_ray_1d_length;
	vector_t		v_map_check;
	vector_t		v_step;
	ray_t			*ray;

	v_map_check.x = (int)cub3d->player.pos.x;
	v_map_check.y = (int)cub3d->player.pos.y;
	v_ray_step_size = init_step_size(to_radians(dir_to_enemy));
	v_step = init_v_step(dir_to_enemy);
	v_ray_1d_length = init_len(cub3d->player.pos, dir_to_enemy, v_map_check,
			v_ray_step_size);
	ray = init_ray_dir(dir_to_enemy);
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
