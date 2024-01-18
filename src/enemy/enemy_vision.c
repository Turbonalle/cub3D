/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_vision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:31:20 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	handle_movement(t_cub3d *cub3d, double at_target, int target, int i)
{
	if (target == 0)
	{
		enemy_advance(cub3d, i);
		if (dist_between_d_vectors(cub3d->player.pos, cub3d->enemy[i].pos)
			< ENEMY_CATCH_DISTANCE)
		{
			player_is_hit(cub3d, i);
		}
	}
	if (target == 1)
	{
		enemy_advance(cub3d, i);
		if (dist_between_d_vectors(cub3d->enemy[i].pos, cub3d->enemy[i].target)
			< at_target)
		{
			cub3d->enemy[i].is_walking = 0;
			if (cub3d->level->distraction_amount > 0
				&& cub3d->enemy[i].target.x == cub3d->level->distraction.x
				&& cub3d->enemy[i].target.y == cub3d->level->distraction.y)
			{
				cub3d->enemy[i].is_eating = 1;
			}
		}
	}
}

static double	get_dir_player(t_cub3d *cub3d, int i)
{
	return (within_360(atan2(cub3d->player.pos.y
				- cub3d->enemy[i].pos.y, cub3d->player.pos.x
				- cub3d->enemy[i].pos.x) * 180 / M_PI));
}

static int	get_e_enemy_state(t_enemy enemy)
{
	if (enemy.is_hunting)
		return (HUNTING);
	else if (enemy.is_walking)
		return (WALKING);
	else
		return (IDLE);
}

void	enemy_vision(t_cub3d *cub3d)
{
	int		i;
	double	at_target;

	i = 0;
	at_target = ENEMY_SPEED * (1 + cub3d->settings.e_speed) * 2;
	while (i < cub3d->num_enemies)
	{
		cub3d->enemy[i].dir_player = get_dir_player(cub3d, i);
		cub3d->enemy[i].is_hunting = FALSE;
		if (cub3d->run_time > cub3d->enemy[i].freeze_start + ENEMY_FREEZE)
		{
			if (cub3d->enemy[i].is_eating)
				eat(cub3d, i);
			else if (distraction(cub3d, i))
				handle_movement(cub3d, at_target, 1, i);
			else if (check_if_player_is_seen(cub3d, i))
				handle_movement(cub3d, at_target, 0, i);
			else if (cub3d->enemy[i].is_walking)
				handle_movement(cub3d, at_target, 1, i);
			else
				spin(cub3d, i, at_target);
		}
		cub3d->enemy[i].state = get_e_enemy_state(cub3d->enemy[i]);
		i++;
	}
}
