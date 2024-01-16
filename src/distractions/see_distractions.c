/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   see_distractions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:16:12 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 23:19:23 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	ray_to_distraction(cub3d_t *cub3d, double dir_to_distraction, int i)
{
	dvector_t		v_ray_step_size;
	dvector_t		v_ray_1d_length;
	double			max_dist;
	vector_t		v_map_check;
	vector_t		v_step;
	ray_t			*ray;

	max_dist = sqrt(pow(cub3d->player.pos.x
				- cub3d->level->distractions[i].pos.x, 2)
			+ pow(cub3d->player.pos.y
				- cub3d->level->distractions[i].pos.y, 2));
	v_map_check.x = (int)cub3d->player.pos.x;
	v_map_check.y = (int)cub3d->player.pos.y;
	v_ray_step_size = init_step_size(to_radians(dir_to_distraction));
	v_step = init_v_step(dir_to_distraction);
	v_ray_1d_length = init_len(cub3d->player.pos, dir_to_distraction,
			v_map_check, v_ray_step_size);
	ray = init_ray_dir(dir_to_distraction);
	if (!ray)
		return (0);
	while (ray->length < max_dist)
	{
		if (wall_or_door_found(cub3d, v_map_check))
			return (free(ray), 0);
		adjust(&v_map_check, ray, v_step, &v_ray_1d_length);
		adjust_no_flag(&v_ray_1d_length, v_ray_step_size);
	}
	free(ray);
	return (1);
}

static void	see_distraction(cub3d_t *cub3d, double dir_to_distraction, int i)
{
	double	angle_min;
	double	angle_max;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	cub3d->level->distractions[i].visible = FALSE;
	if (angle_max < angle_min)
	{
		if (cub3d->fov < 360 && dir_to_distraction > angle_max
			&& dir_to_distraction < angle_min)
			return ;
		else if (!ray_to_distraction(cub3d, dir_to_distraction, i))
			return ;
	}
	else
	{
		if (cub3d->fov < 360 && (dir_to_distraction < angle_min
				|| dir_to_distraction > angle_max))
			return ;
		else if (!ray_to_distraction(cub3d, dir_to_distraction, i))
			return ;
	}
	cub3d->level->distractions[i].visible = TRUE;
	draw_distraction(cub3d, dir_to_distraction, i);
	return ;
}

void	check_distraction(cub3d_t *cub3d, int i)
{
	double		dir_to_distraction;

	dir_to_distraction = within_360((atan2(cub3d->level->distractions[i].pos.y
					- cub3d->player.pos.y, cub3d->level->distractions[i].pos.x
					- cub3d->player.pos.x) * 180 / M_PI));
	if (cub3d->level->distractions[i].collected == FALSE)
		see_distraction(cub3d, dir_to_distraction, i);
}
