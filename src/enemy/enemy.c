/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:04:10 by slampine          #+#    #+#             */
/*   Updated: 2023/12/29 13:47:24 by slampine         ###   ########.fr       */
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

static int	wall_or_door_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	if (vMapCheck.x >= 0
		&& vMapCheck.x < cub3d->level->map_columns
		&& vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->level->map_rows
		&& cub3d->level->map[vMapCheck.y][vMapCheck.x] == WALL)
		return (1);
	if (vMapCheck.x >= 0
		&& vMapCheck.x < cub3d->level->map_columns && vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->level->map_rows
		&& (cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'A'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'B'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'C'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'D'))
	{
		if (dist_between(vMapCheck, cub3d->player.pos) > 4)
			return (1);
		if (check_if_door_open(cub3d, vMapCheck.x, vMapCheck.y))
			return (0);
		else
			return (1);
	}
	return (0);
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

int	enemy_ray(cub3d_t *cub3d, player_t player, t_enemy *enemy, int i)
{
	dvector_t		vRayUnitStepSize;
	dvector_t		vRayLength1D;
	vector_t		vMapCheck;
	vector_t		vStep;
	ray_t			*ray;

	vMapCheck.x = (int)enemy[i].pos.x;
	vMapCheck.y = (int)enemy[i].pos.y;
	vRayUnitStepSize = init_step_size(to_radians(enemy[i].dir_player));
	vStep = init_v_step(enemy[i].dir_player);
	vRayLength1D = init_ray_1D_length(cub3d->enemy[i].pos, enemy[i].dir_player, vMapCheck, vRayUnitStepSize);
	ray = init_ray(enemy, i);
	if (!ray)
		return (0);
	while (not_at_end(ray, player, enemy, i))
	{
		if (wall_or_door_found(cub3d, vMapCheck))
			return (free(ray), 0);
		adjust(&vMapCheck, ray, vStep, &vRayLength1D);
		adjust_no_flag(&vRayLength1D, vRayUnitStepSize);
	}
	enemy[i].angle = to_radians(ray->angle);
	enemy[i].target = cub3d->player.pos;
	free(ray);
	return (1);
}

void	handle_movement(cub3d_t *cub3d, double at_target, int target, int i)
{
	if (target == 0)
	{
		enemy_advance(cub3d, i);
		cub3d->enemy[i].is_walking = 1;
		if (sqrt(pow(cub3d->player.pos.x - cub3d->enemy[i].pos.x, 2)
				+ pow(cub3d->player.pos.y - cub3d->enemy[i].pos.y, 2)) < 1)
		{
			cub3d->enemy[i].freeze_start = cub3d->run_time;
			printf("You were caught at time %f\n",cub3d->run_time);
			player_is_hit(cub3d);
		}
	}
	if (target == 1)
	{
		enemy_advance(cub3d, i);
		cub3d->enemy[i].is_walking = 1;
		if (sqrt(pow(cub3d->enemy[i].target.x - cub3d->enemy[i].pos.x, 2) + pow(cub3d->enemy[i].target.y - cub3d->enemy[i].pos.y, 2)) < at_target)
		{
			cub3d->enemy[i].is_walking = 0;
			if (cub3d->level->distraction_amount > 0 && cub3d->enemy[i].target.x == cub3d->level->distraction.x && cub3d->enemy[i].target.y == cub3d->level->distraction.y)
			{
				printf("Started eating at %f\n",cub3d->run_time);
				cub3d->enemy[i].is_eating = 1;
			}
		}
	}
}

void	enemy_vision(cub3d_t *cub3d)
{
	int		i;
	double	at_target;

	i = 0;
	at_target = ENEMY_SPEED * (1 + cub3d->settings.e_speed) * 2;
	while (i < cub3d->num_enemies)
	{
		cub3d->enemy[i].is_hunting = FALSE;
		if (cub3d->run_time > cub3d->enemy[i].freeze_start + ENEMY_FREEZE)
		{
			if (check_if_player_is_seen(cub3d, i))
				handle_movement(cub3d, at_target, 0, i);
			else if (distraction(cub3d, i))
				handle_movement(cub3d, at_target, 1, i);
			else if (cub3d->enemy[i].is_walking)
				handle_movement(cub3d, at_target, 1, i);
			else if (cub3d->enemy[i].is_eating)
				eat(cub3d, i);
			else
				spin(cub3d, i, at_target);
		}
		if (cub3d->enemy[i].is_walking)
			cub3d->enemy[i].state = WALKING;
		else
			cub3d->enemy[i].state = IDLE;
		i++;
	}
}
