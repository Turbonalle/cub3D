/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:04:10 by slampine          #+#    #+#             */
/*   Updated: 2024/01/02 12:50:05 by slampine         ###   ########.fr       */
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
	ray->end.x = 0;
	ray->end.y = 0;
	return (ray);
}

dvector_t	shorten_vector(dvector_t pos, dvector_t target)
{
	double		multi;
	dvector_t	len_target;
	dvector_t	result;

	multi = (rand() % 81 + 20) / 100.0;
	len_target.x = target.x - pos.x;
	len_target.y = target.y - pos.y;
	result.x = pos.x + (multi * len_target.x);
	result.y = pos.y + (multi * len_target.y);
	return (result);
}

static void	update_end(cub3d_t *cub3d, ray_t *ray, int i)
{
	dvector_t		v_ray_dir;

	v_ray_dir.x = cos((cub3d->enemy[i].angle));
	v_ray_dir.y = sin((cub3d->enemy[i].angle));
	ray->end.x = cub3d->enemy[i].pos.x + v_ray_dir.x * ray->length;
	ray->end.y = cub3d->enemy[i].pos.y + v_ray_dir.y * ray->length;
}

static void	update_and_free(cub3d_t *cub3d, ray_t *ray, int i)
{
	update_end(cub3d, ray, i);
	cub3d->enemy[i].target = ray->end;
	cub3d->enemy[i].target = shorten_vector(cub3d->enemy[i].pos,
			cub3d->enemy[i].target);
	free(ray);
}

int	enemy_movement_ray(cub3d_t *cub3d, t_enemy *enemy, int i, double max_dist)
{
	dvector_t		v_ray_step_size;
	dvector_t		v_ray_1d_length;
	vector_t		v_map_check;
	vector_t		v_step;
	ray_t			*ray;

	v_map_check.x = (int)enemy[i].pos.x;
	v_map_check.y = (int)enemy[i].pos.y;
	v_ray_step_size = init_step_size(enemy[i].angle);
	v_step = init_v_step(enemy[i].angle * 180 / M_PI);
	v_ray_1d_length = init_ray_1D_length(cub3d->enemy[i].pos,
			enemy[i].angle * 180 / M_PI, v_map_check, v_ray_step_size);
	ray = init_ray(enemy, i);
	if (!ray)
		return (0);
	while (ray->length < max_dist)
	{
		adjust(&v_map_check, ray, v_step, &v_ray_1d_length);
		adjust_no_flag(&v_ray_1d_length, v_ray_step_size);
		if (wall_or_door_found(cub3d, v_map_check) && ray->length < max_dist)
			return (update_and_free(cub3d, ray, i), 0);
	}
	free(ray);
	return (1);
}
