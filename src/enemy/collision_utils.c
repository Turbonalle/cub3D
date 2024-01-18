/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:39:20 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	check_each_other(t_cub3d *cub3d, int i, t_dvector new_pos)
{
	int			j;

	j = -1;
	while (++j < cub3d->num_enemies)
	{
		if (i == j)
			continue ;
		if (dist_between_d_vectors(new_pos, cub3d->enemy[j].pos)
			< 1.3 * ENEMY_RADIUS)
			return (1);
	}
	return (0);
}

int	check_first_eight(t_cub3d *cub3d, int i, t_dvector new_pos)
{
	if (cub3d->enemy[i].angle > M_PI * 15 / 8
		|| cub3d->enemy[i].angle < M_PI * 1 / 8)
	{
		if (check_pos(cub3d, (int)(new_pos.y - ENEMY_RADIUS),
			(int)(new_pos.x + ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y), (int)(new_pos.x + ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y + ENEMY_RADIUS),
			(int)(new_pos.x + ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (1);
		}
	}
	return (0);
}

int	check_second_eight(t_cub3d *cub3d, int i, t_dvector new_pos)
{
	if (cub3d->enemy[i].angle < M_PI * 3 / 8)
	{
		if (check_pos(cub3d, (int)(new_pos.y), (int)(new_pos.x + ENEMY_RADIUS)))
		{
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y + ENEMY_RADIUS),
			(int)(new_pos.x + ENEMY_RADIUS)))
		{
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y + ENEMY_RADIUS), (int)(new_pos.x)))
		{
			return (1);
		}
	}
	return (0);
}

int	check_third_eight(t_cub3d *cub3d, int i, t_dvector new_pos)
{
	if (cub3d->enemy[i].angle < M_PI * 5 / 8)
	{
		if (check_pos(cub3d, (int)(new_pos.y + ENEMY_RADIUS),
			(int)(new_pos.x + ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y + ENEMY_RADIUS), (int)(new_pos.x)))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y + ENEMY_RADIUS),
			(int)(new_pos.x - ENEMY_RADIUS)))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (1);
		}
	}
	return (0);
}

int	check_fourth_eight(t_cub3d *cub3d, int i, t_dvector new_pos)
{
	if (cub3d->enemy[i].angle < M_PI * 7 / 8)
	{
		if (check_pos(cub3d, (int)(new_pos.y + ENEMY_RADIUS), (int)(new_pos.x)))
		{
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y + ENEMY_RADIUS),
			(int)(new_pos.x - ENEMY_RADIUS)))
		{
			return (1);
		}
		if (check_pos(cub3d, (int)(new_pos.y), (int)(new_pos.x - ENEMY_RADIUS)))
		{
			return (1);
		}
	}
	return (0);
}
