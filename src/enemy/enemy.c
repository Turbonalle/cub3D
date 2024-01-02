/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:04:10 by slampine          #+#    #+#             */
/*   Updated: 2024/01/02 11:58:42 by slampine         ###   ########.fr       */
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
	dvector_t		vRayDir;

	vRayDir.x = cos((cub3d->enemy[i].angle));
	vRayDir.y = sin((cub3d->enemy[i].angle));
	ray->end.x = cub3d->enemy[i].pos.x + vRayDir.x * ray->length;
	ray->end.y = cub3d->enemy[i].pos.y + vRayDir.y * ray->length;
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
	dvector_t		vRayUnitStepSize;
	dvector_t		vRayLength1D;
	vector_t		vMapCheck;
	vector_t		vStep;
	ray_t			*ray;

	vMapCheck.x = (int)enemy[i].pos.x;
	vMapCheck.y = (int)enemy[i].pos.y;
	vRayUnitStepSize = init_step_size(enemy[i].angle);
	vStep = init_v_step(enemy[i].angle * 180 / M_PI);
	vRayLength1D = init_ray_1D_length(cub3d->enemy[i].pos,
			enemy[i].angle * 180 / M_PI, vMapCheck, vRayUnitStepSize);
	ray = init_ray(enemy, i);
	if (!ray)
		return (0);
	while (ray->length < max_dist)
	{
		adjust(&vMapCheck, ray, vStep, &vRayLength1D);
		adjust_no_flag(&vRayLength1D, vRayUnitStepSize);
		if (wall_or_door_found(cub3d, vMapCheck) && ray->length < max_dist)
			return (update_and_free(cub3d, ray, i), 0);
	}
	free(ray);
	return (1);
}
