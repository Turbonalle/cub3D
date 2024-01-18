/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game_entities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:42 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 11:06:24 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	draw_all_entities_in_order(t_cub3d *cub3d)
{
	t_key_node		**ordered_keys;
	t_enemy			**ordered_enemies;
	t_distract	**ordered_distractions;

	ordered_keys = create_array_of_keys_ordered_by_dist(cub3d);
	ordered_enemies = create_array_of_enemies_ordered_by_dist(cub3d);
	ordered_distractions = create_array_of_distractions_ordered_by_dist(cub3d);
	if (!ordered_keys || !ordered_enemies || !ordered_distractions)
		return (FAIL);
	assign_z_depth_ordered_by_distance(cub3d, ordered_enemies,
		ordered_keys, ordered_distractions);
	draw_all_enemies(cub3d, ordered_enemies);
	draw_all_distractions(cub3d, ordered_distractions);
	draw_all_keys(cub3d);
	free(ordered_enemies);
	free(ordered_keys);
	free(ordered_distractions);
	return (SUCCESS);
}

int	draw_game_entities(t_cub3d *cub3d)
{
	int	animation_frame_change;
	int	fps_frame_change;

	animation_frame_change = animation_frames_changed(cub3d);
	fps_frame_change = fps_frame_changed(cub3d);
	if (animation_frame_change || fps_frame_change)
	{
		if (draw_all_entities_in_order(cub3d) == FAIL)
			return (FAIL);
	}
	if (animation_frame_change)
		update_prev_frames(cub3d);
	return (SUCCESS);
}
