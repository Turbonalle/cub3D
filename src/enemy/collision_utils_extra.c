/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:44:27 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 09:56:08 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

dvector_t	set_new_pos(cub3d_t *cub3d, int i)
{
	dvector_t	new_pos;
	double		step;

	new_pos.x = cub3d->enemy[i].pos.x + cos(cub3d->enemy[i].angle)
		* ENEMY_SPEED * (1 + cub3d->settings.e_speed);
	new_pos.y = cub3d->enemy[i].pos.y + sin(cub3d->enemy[i].angle)
		* ENEMY_SPEED * (1 + cub3d->settings.e_speed);
	step = dist_between_d_vectors(cub3d->enemy[i].pos, new_pos);
	if (step > ENEMY_CATCH_DISTANCE)
		new_pos = cub3d->enemy[i].target;
	return (new_pos);
}

int	check_fifth_eight(cub3d_t *cub3d, int i, dvector_t new_pos)
{
	if (cub3d->enemy[i].angle < M_PI * 9 / 8)
	{
		if (check_pos(cub3d, (int)(new_pos.y + ENEMY_RADIUS),
			(int)(new_pos.x - ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y), (int)(new_pos.x - ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS),
			(int)(new_pos.x - ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (1);
		}
	}
	return (0);
}

int	check_sixth_eight(cub3d_t *cub3d, int i, dvector_t new_pos)
{
	if (cub3d->enemy[i].angle < M_PI * 11 / 8)
	{
		if (check_pos(cub3d, (int)(new_pos.y), (int)(new_pos.x - ENEMY_RADIUS)))
		{
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS),
			(int)(new_pos.x - ENEMY_RADIUS)))
		{
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x)))
		{
			return (1);
		}
	}
	return (0);
}

int	check_seventh_eight(cub3d_t *cub3d, int i, dvector_t new_pos)
{
	if (cub3d->enemy[i].angle < M_PI * 13 / 8)
	{
		if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS),
			(int)(new_pos.x - ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x)))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS),
			(int)(new_pos.x + ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (1);
		}
	}
	return (0);
}

int	check_eighth_eight(cub3d_t *cub3d, dvector_t new_pos)
{
	if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x)))
	{
		return (1);
	}
	if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS),
		(int)(new_pos.x + ENEMY_RADIUS)))
	{
		return (1);
	}
	if (check_pos(cub3d, (int)(new_pos.y), (int)(new_pos.x + ENEMY_RADIUS)))
	{
		return (1);
	}
	return (0);
}
