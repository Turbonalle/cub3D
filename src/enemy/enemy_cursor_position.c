/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_cursor_position.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:21:02 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 20:22:06 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	cursor_right_side(cub3d_t *cub3d, double cursor_angle,
	dvector_t *position)
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

static void	cursor_left_side(cub3d_t *cub3d, double cursor_angle,
	dvector_t *position)
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

void	set_enemy_cursor_position(cub3d_t *cub3d, double cursor_angle,
	dvector_t *position)
{
	if (cursor_angle <= 180)
		cursor_right_side(cub3d, cursor_angle, position);
	else
		cursor_left_side(cub3d, cursor_angle, position);
}
