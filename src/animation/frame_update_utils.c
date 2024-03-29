/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_update_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:38 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:56:53 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	animation_frames_changed(t_cub3d *cub3d)
{
	int	i;

	cub3d->curr_frame_index_idle = (int)(cub3d->run_time
			/ ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_ENEMY_IDLE;
	if (cub3d->prev_frame_index_idle != cub3d->curr_frame_index_idle)
	{
		cub3d->curr_frame_index_walking = (int)(cub3d->run_time
				/ ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_WALKING;
		cub3d->curr_frame_index_hunting = (int)(cub3d->run_time
				/ ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_HUNTING;
		i = 0;
		while (i < NUM_DOORS_MAX)
		{
			if (cub3d->level->door_groups[i].num_keys_left > 0)
				cub3d->level->key_groups[i].curr_frame_index
					= (int)(cub3d->run_time / ANIMATION_INTERVAL_MS
						* 1000) % NUM_FRAMES_KEY;
			i++;
		}
		return (TRUE);
	}
	return (FALSE);
}

int	fps_frame_changed(t_cub3d *cub3d)
{
	if (cub3d->run_time - cub3d->prev_frame_update_timestamp
		>= cub3d->frame_time)
	{
		cub3d->prev_frame_update_timestamp = cub3d->run_time;
		return (TRUE);
	}
	return (FALSE);
}

void	update_prev_frames(t_cub3d *cub3d)
{
	int	i;

	cub3d->prev_frame_index_idle = cub3d->curr_frame_index_idle;
	cub3d->prev_frame_index_walking = cub3d->curr_frame_index_walking;
	cub3d->prev_frame_index_hunting = cub3d->curr_frame_index_hunting;
	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		if (cub3d->level->door_groups[i].num_keys_left > 0)
			cub3d->level->key_groups[i].prev_frame_index
				= cub3d->level->key_groups[i].curr_frame_index;
		i++;
	}
}
