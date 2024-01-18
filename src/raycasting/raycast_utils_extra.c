/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_extra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:00:05 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 13:06:30 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	update_end(t_cub3d *cub3d, double dir, t_ray *ray)
{
	t_dvector	v_ray_dir;

	v_ray_dir.x = cos(dir);
	v_ray_dir.y = sin(dir);
	ray->end.x = cub3d->player.pos.x + v_ray_dir.x * ray->length;
	ray->end.y = cub3d->player.pos.y + v_ray_dir.y * ray->length;
}

static double	dist_to_door(t_player player, t_vector door)
{
	double		dist;
	t_dvector	door_middle;

	door_middle.x = door.x + 0.5;
	door_middle.y = door.y + 0.5;
	dist = dist_between_d_vectors(door_middle, player.pos);
	return (dist);
}

static int	door_found(t_cub3d *cub3d, t_vector v_map_check)
{
	double	dist;

	if (v_map_check.x >= 0 && v_map_check.x
		< cub3d->level->map_columns && v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& (cub3d->level->map[v_map_check.y][v_map_check.x] == 'A'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'B'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'C'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'D'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'O'))
	{
		dist = dist_to_door(cub3d->player, v_map_check);
		if (dist > 2)
			return (SUCCESS);
		if (check_if_door_unlocked(cub3d, v_map_check.x, v_map_check.y))
			return (FAIL);
		else
			return (SUCCESS);
	}
	return (FAIL);
}

int	obstacle_found(t_cub3d *cub3d, t_vector v_map_check, t_ray *ray, double dir)
{
	if (wall_found(cub3d, v_map_check))
	{
		ray->target = cub3d->level->map[v_map_check.y][v_map_check.x];
		update_end(cub3d, dir, ray);
		return (SUCCESS);
	}
	if (goal_found(cub3d, v_map_check))
	{
		ray->target = cub3d->level->map[v_map_check.y][v_map_check.x];
		update_end(cub3d, dir, ray);
		return (SUCCESS);
	}
	if (door_found(cub3d, v_map_check))
	{
		ray->target = cub3d->level->map[v_map_check.y][v_map_check.x];
		if (check_if_door_unlocked(cub3d, v_map_check.x, v_map_check.y))
			ray->target = 'O';
		update_end(cub3d, dir, ray);
		return (SUCCESS);
	}
	return (FAIL);
}
