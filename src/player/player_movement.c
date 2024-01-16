/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:00:10 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 12:50:30 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	is_walking(cub3d_t *cub3d)
{
	return ((cub3d->keys.w && !cub3d->keys.s)
		|| (!cub3d->keys.w && cub3d->keys.s));
}

int	is_strafing(cub3d_t *cub3d)
{
	return ((cub3d->keys.a && !cub3d->keys.d)
		|| (!cub3d->keys.a && cub3d->keys.d));
}

void	player_rotation(cub3d_t *cub3d)
{
	if (cub3d->settings.mouse == FALSE)
	{
		if (cub3d->keys.left && !cub3d->keys.right)
		{
			cub3d->player.angle -= ROTATION_SPEED * cub3d->delta_time;
			cub3d->player.angle = within_two_pi(cub3d->player.angle);
		}
		else if (cub3d->keys.right && !cub3d->keys.left)
		{
			cub3d->player.angle += ROTATION_SPEED * cub3d->delta_time;
			if (cub3d->player.angle >= (2 * M_PI))
				cub3d->player.angle -= (M_PI + M_PI);
		}
	}
	else
	{
		if (cub3d->mouse.x != cub3d->mouse_set_pos.x)
		{
			cub3d->player.angle += (cub3d->mouse.x - cub3d->mouse_set_pos.x)
				* cub3d->settings.mouse_sensitivity;
			cub3d->player.angle = within_two_pi(cub3d->player.angle);
			cub3d->mouse_set_pos.x = cub3d->mouse.x;
		}
	}
}
