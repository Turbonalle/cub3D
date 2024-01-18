/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_cursor_position.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:21:02 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	cursor_right_side(t_cub3d *cub3d, double cursor_angle,
	t_dvector *position)
{
	double	theta;

	theta = 180 - cursor_angle;
	position->x = cub3d->img->width / 2 + tan(to_radians(theta))
		* (cub3d->img->height / 2 - ENEMY_CURSOR_MARGIN);
	position->y = cub3d->img->height - ENEMY_CURSOR_MARGIN;
	if (position->x > cub3d->img->width - ENEMY_CURSOR_MARGIN)
	{
		theta = cursor_angle - 90;
		position->x = cub3d->img->width - ENEMY_CURSOR_MARGIN;
		position->y = cub3d->img->height / 2 + tan(to_radians(theta))
			* (cub3d->img->width / 2 - ENEMY_CURSOR_MARGIN);
	}
}

static void	cursor_left_side(t_cub3d *cub3d, double cursor_angle,
	t_dvector *position)
{
	double	theta;

	theta = cursor_angle - 180;
	position->x = cub3d->img->width / 2 - tan(to_radians(theta))
		* (cub3d->img->height / 2 - ENEMY_CURSOR_MARGIN);
	position->y = cub3d->img->height - ENEMY_CURSOR_MARGIN;
	if (position->x < ENEMY_CURSOR_MARGIN)
	{
		theta = 270 - cursor_angle;
		position->x = ENEMY_CURSOR_MARGIN;
		position->y = cub3d->img->height / 2 + tan(to_radians(theta))
			* (cub3d->img->width / 2 - ENEMY_CURSOR_MARGIN);
	}
}

void	set_enemy_cursor_position(t_cub3d *cub3d, double cursor_angle,
	t_dvector *position)
{
	if (cursor_angle <= 180)
		cursor_right_side(cub3d, cursor_angle, position);
	else
		cursor_left_side(cub3d, cursor_angle, position);
}
