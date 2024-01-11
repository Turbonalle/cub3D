/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:36:37 by slampine          #+#    #+#             */
/*   Updated: 2024/01/11 17:36:38 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	player_walking(cub3d_t *cub3d)
{
	if (cub3d->keys.w && !cub3d->keys.s)
	{
		cub3d->player.movement_angle = cub3d->player.angle;
		cub3d->player.new_pos.x += cos(cub3d->player.angle)
			* MOVEMENT_SPEED * cub3d->delta_time;
		cub3d->player.new_pos.y += sin(cub3d->player.angle)
			* MOVEMENT_SPEED * cub3d->delta_time;
	}
	else if (!cub3d->keys.w && cub3d->keys.s)
	{
		cub3d->player.movement_angle = within_two_pi(cub3d->player.angle
				+ to_radians(180));
		cub3d->player.new_pos.x -= cos(cub3d->player.angle)
			* MOVEMENT_SPEED * cub3d->delta_time;
		cub3d->player.new_pos.y -= sin(cub3d->player.angle)
			* MOVEMENT_SPEED * cub3d->delta_time;
	}
}

void	player_strafing(cub3d_t *cub3d)
{
	if (cub3d->keys.a && !cub3d->keys.d)
	{
		cub3d->player.movement_angle = within_two_pi(cub3d->player.angle
				- to_radians(90));
		cub3d->player.new_pos.x += cos(cub3d->player.movement_angle)
			* MOVEMENT_SPEED * cub3d->delta_time;
		cub3d->player.new_pos.y += sin(cub3d->player.movement_angle)
			* MOVEMENT_SPEED * cub3d->delta_time;
	}
	else if (!cub3d->keys.a && cub3d->keys.d)
	{
		cub3d->player.movement_angle = within_two_pi(cub3d->player.angle
				+ to_radians(90));
		cub3d->player.new_pos.x += cos(cub3d->player.movement_angle)
			* MOVEMENT_SPEED * cub3d->delta_time;
		cub3d->player.new_pos.y += sin(cub3d->player.movement_angle)
			* MOVEMENT_SPEED * cub3d->delta_time;
	}
}

void	player_both(cub3d_t *cub3d)
{
	if (cub3d->keys.w && cub3d->keys.a)
	{
		cub3d->player.movement_angle = within_two_pi(cub3d->player.angle
				- to_radians(45));
	}
	else if (cub3d->keys.w && cub3d->keys.d)
	{
		cub3d->player.movement_angle = within_two_pi(cub3d->player.angle
				+ to_radians(45));
	}
	else if (cub3d->keys.s && cub3d->keys.a)
	{
		cub3d->player.movement_angle = within_two_pi(cub3d->player.angle
				- to_radians(135));
	}
	else if (cub3d->keys.s && cub3d->keys.d)
	{
		cub3d->player.movement_angle = within_two_pi(cub3d->player.angle
				+ to_radians(135));
	}
	cub3d->player.new_pos.x += cos(cub3d->player.movement_angle)
		* MOVEMENT_SPEED * cub3d->delta_time;
	cub3d->player.new_pos.y += sin(cub3d->player.movement_angle)
		* MOVEMENT_SPEED * cub3d->delta_time;
}

void	player_movement(cub3d_t *cub3d)
{
	player_rotation(cub3d);
	cub3d->player.is_walking = is_walking(cub3d);
	cub3d->player.is_strafing = is_strafing(cub3d);
	if (!cub3d->player.is_walking && !cub3d->player.is_strafing)
		return ;
	cub3d->player.new_pos = cub3d->player.pos;
	if (cub3d->player.is_walking && !cub3d->player.is_strafing)
		player_walking(cub3d);
	else if (!cub3d->player.is_walking && cub3d->player.is_strafing)
		player_strafing(cub3d);
	else
		player_both(cub3d);
	collision_checker(cub3d);
}
