/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:44:27 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

t_dvector	set_new_pos(t_cub3d *cub3d, int i)
{
	t_dvector	new_pos;
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

int	check_fifth_eight(t_cub3d *cub3d, int i, t_dvector new_pos)
{
	if (cub3d->enemy[i].angle < M_PI * 9 / 8)
	{
		if (check_pos(cub3d, (int)(new_pos.y + ENEMY_RADIUS),
			(int)(new_pos.x - ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (SUCCESS);
		}
		if (check_pos(cub3d, (int)(new_pos.y), (int)(new_pos.x - ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (SUCCESS);
		}
		if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS),
			(int)(new_pos.x - ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (SUCCESS);
		}
	}
	return (FAIL);
}

int	check_sixth_eight(t_cub3d *cub3d, int i, t_dvector new_pos)
{
	if (cub3d->enemy[i].angle < M_PI * 11 / 8)
	{
		if (check_pos(cub3d, (int)(new_pos.y), (int)(new_pos.x - ENEMY_RADIUS)))
		{
			return (SUCCESS);
		}
		if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS),
			(int)(new_pos.x - ENEMY_RADIUS)))
		{
			return (SUCCESS);
		}
		if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x)))
		{
			return (SUCCESS);
		}
	}
	return (FAIL);
}

int	check_seventh_eight(t_cub3d *cub3d, int i, t_dvector new_pos)
{
	if (cub3d->enemy[i].angle < M_PI * 13 / 8)
	{
		if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS),
			(int)(new_pos.x - ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (SUCCESS);
		}
		if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x)))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (SUCCESS);
		}
		if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS),
			(int)(new_pos.x + ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (SUCCESS);
		}
	}
	return (FAIL);
}

int	check_eighth_eight(t_cub3d *cub3d, t_dvector new_pos)
{
	if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x)))
	{
		return (SUCCESS);
	}
	if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS),
		(int)(new_pos.x + ENEMY_RADIUS)))
	{
		return (SUCCESS);
	}
	if (check_pos(cub3d, (int)(new_pos.y), (int)(new_pos.x + ENEMY_RADIUS)))
	{
		return (SUCCESS);
	}
	return (FAIL);
}
