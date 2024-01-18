/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:59:13 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/18 13:08:15 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	all_keys_found(t_cub3d *cub3d, int i)
{
	t_key_node	*temp;

	if (i > NUM_DOORS_MAX)
		return (SUCCESS);
	temp = cub3d->level->key_groups[i].keys;
	while (temp != NULL)
	{
		if (temp->collected == 0)
			return (FAIL);
		temp = temp->next;
	}
	return (SUCCESS);
}

t_dvector	init_step_size(double angle)
{
	t_dvector	v_ray_step_size;
	t_dvector	v_ray_dir;

	v_ray_dir.x = cos(angle);
	v_ray_dir.y = sin(angle);
	v_ray_step_size.x = sqrt(1 + (v_ray_dir.y / v_ray_dir.x) * (v_ray_dir.y
				/ v_ray_dir.x));
	v_ray_step_size.y = sqrt(1 + (v_ray_dir.x / v_ray_dir.y) * (v_ray_dir.x
				/ v_ray_dir.y));
	return (v_ray_step_size);
}

int	obstacle_found_dist(t_cub3d *cub3d, t_vector v_map_check, int dist)
{
	if (v_map_check.x >= 0
		&& v_map_check.x < cub3d->level->map_columns
		&& v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& (cub3d->level->map[v_map_check.y][v_map_check.x] == WALL
	))
		return (SUCCESS);
	if (v_map_check.x >= 0 && v_map_check.x < cub3d->level->map_columns
		&& v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& (cub3d->level->map[v_map_check.y][v_map_check.x] == 'A'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'B'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'C'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'D'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'O'))
	{
		if (dist > 1)
			return (SUCCESS);
		if (check_if_door_unlocked(cub3d, v_map_check.x, v_map_check.y))
			return (FAIL);
		else
			return (SUCCESS);
	}
	return (FAIL);
}

int	wall_checker(int wall_flag, t_dvector end, t_dvector pos)
{
	if (wall_flag == 0 && pos.y < end.y)
		return (NO);
	else if (wall_flag == 0 && pos.y >= end.y)
		return (SO);
	else if (wall_flag == 1 && end.x > pos.x)
		return (WE);
	else if (wall_flag == 1)
		return (EA);
	else
		return (NO_WALL);
}
