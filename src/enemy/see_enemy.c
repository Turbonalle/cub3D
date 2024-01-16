/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   see_enemy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:25:03 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 23:40:59 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static double	calculate_dir_to_enemy(cub3d_t *cub3d, int i)
{
	return (within_360((atan2(cub3d->enemy[i].pos.y
					- cub3d->player.pos.y,
					cub3d->enemy[i].pos.x
					- cub3d->player.pos.x) * 180 / M_PI)));
}

static int	enemy_chasing_behind(cub3d_t *cub3d, double dir_to_enemy,
		double angle_min, double angle_max)
{
	return (cub3d->fov < 360 && dir_to_enemy
		> angle_max && dir_to_enemy < angle_min);
}

static void	draw_cursor_if_needed(cub3d_t *cub3d, int i, double dir_to_enemy)
{
	if (cub3d->enemy[i].is_hunting)
		enemy_cursor(cub3d, dir_to_enemy, dist_between_d_vectors(
				cub3d->enemy[i].pos, cub3d->player.pos));
}

static void	see_visible_enemy(cub3d_t *cub3d, int i, double dir_to_enemy)
{
	cub3d->enemy[i].visible = TRUE;
	draw_enemy(cub3d, dir_to_enemy, i);
}

void	see_enemy(cub3d_t *cub3d, int i)
{
	double	angle_min;
	double	angle_max;
	double	max_dist;
	double	dir_to_enemy;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	max_dist = dist_between_d_vectors(cub3d->player.pos, cub3d->enemy[i].pos);
	dir_to_enemy = calculate_dir_to_enemy(cub3d, i);
	cub3d->enemy[i].visible = FALSE;
	if (angle_max < angle_min)
	{
		if (enemy_chasing_behind(cub3d, dir_to_enemy, angle_min, angle_max))
			draw_cursor_if_needed(cub3d, i, dir_to_enemy);
		else if (ray_to_enemy(cub3d, dir_to_enemy, max_dist))
			see_visible_enemy(cub3d, i, dir_to_enemy);
	}
	else
	{
		if (enemy_chasing_behind(cub3d, dir_to_enemy, angle_min, angle_max))
			draw_cursor_if_needed(cub3d, i, dir_to_enemy);
		else if (ray_to_enemy(cub3d, dir_to_enemy, max_dist))
			see_visible_enemy(cub3d, i, dir_to_enemy);
	}
}
