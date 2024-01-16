/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_spin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:14:24 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 22:39:58 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	start_spinning(cub3d_t *cub3d, int i)
{
	cub3d->enemy[i].angle_start = within_two_pi(cub3d->enemy[i].angle
			- to_radians(ENEMY_ROT_SPEED));
	cub3d->enemy[i].is_spinning = 1;
}

static void	update_angle(cub3d_t *cub3d, int i)
{
	cub3d->enemy[i].angle = within_two_pi(cub3d->enemy[i].angle
			+ to_radians(ENEMY_ROT_SPEED));
}

static int	should_reset_angle(cub3d_t *cub3d, int i)
{
	return (cub3d->settings.e_behaviour == 2
		|| (cub3d->settings.e_behaviour == 1
			&& fabs(cub3d->enemy[i].angle - cub3d->enemy[i].angle_start)
			< to_radians(ENEMY_ROT_SPEED)));
}

static double	calculate_max_distance(cub3d_t *cub3d)
{
	return (sqrt(cub3d->img->width * cub3d->img->width
			+ cub3d->img->height * cub3d->img->height));
}

void	spin(cub3d_t *cub3d, int i, double at_target)
{
	double	max_dist;

	if (cub3d->enemy[i].is_spinning == 0 && cub3d->settings.e_behaviour < 2)
		start_spinning(cub3d, i);
	update_angle(cub3d, i);
	if (should_reset_angle(cub3d, i))
	{
		cub3d->enemy[i].angle = to_radians(rand() % 360);
		max_dist = calculate_max_distance(cub3d);
		enemy_movement_ray(cub3d, cub3d->enemy, i, max_dist);
		cub3d->enemy[i].angle_start = cub3d->enemy[i].angle;
		while (dist_between_d_vectors(cub3d->enemy[i].pos,
				cub3d->enemy[i].target) < at_target)
		{
			cub3d->enemy[i].angle = within_two_pi(to_radians(2)
					+ cub3d->enemy[i].angle);
			if (fabs(cub3d->enemy[i].angle - cub3d->enemy[i].angle_start)
				< to_radians(1))
				return ;
			enemy_movement_ray(cub3d, cub3d->enemy, i, max_dist);
		}
		cub3d->enemy[i].is_walking = 1;
		enemy_advance(cub3d, i);
		cub3d->enemy[i].is_spinning = 0;
	}
}
