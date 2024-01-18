/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distraction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:34:26 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	ray_to_distraction(t_cub3d *cub3d, double dir_to_distraction,
	double max_dist)
{
	t_dvector		v_ray_step_size;
	t_dvector		v_ray_1d_length;
	t_vector		v_map_check;
	t_vector		v_step;
	t_ray			*ray;

	v_map_check.x = (int)cub3d->player.pos.x;
	v_map_check.y = (int)cub3d->player.pos.y;
	v_ray_step_size = init_step_size(to_radians(dir_to_distraction));
	v_step = init_v_step(dir_to_distraction);
	v_ray_1d_length = init_len(cub3d->player.pos, dir_to_distraction,
			v_map_check, v_ray_step_size);
	ray = init_ray_dir(dir_to_distraction);
	if (!ray)
		return (FAIL);
	while (ray->length < max_dist)
	{
		if (wall_or_door_found(cub3d, v_map_check))
			return (free(ray), 0);
		adjust(&v_map_check, ray, v_step, &v_ray_1d_length);
		adjust_no_flag(&v_ray_1d_length, v_ray_step_size);
	}
	free(ray);
	return (SUCCESS);
}

int	do_distraction_max_smaller(t_cub3d *cub3d, double dir_to_distraction,
	double max_dist)
{
	double	angle_min;
	double	angle_max;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	if (cub3d->fov < 360 && dir_to_distraction > angle_max
		&& dir_to_distraction < angle_min)
		return (FAIL);
	else if (!ray_to_distraction(cub3d, dir_to_distraction, max_dist))
		return (FAIL);
	return (SUCCESS);
}

int	do_distraction_min_smaller(t_cub3d *cub3d, double dir_to_distraction,
	double max_dist)
{
	double	angle_min;
	double	angle_max;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	if (cub3d->fov < 360 && (dir_to_distraction < angle_min
			|| dir_to_distraction > angle_max))
		return (FAIL);
	else if (!ray_to_distraction(cub3d, dir_to_distraction, max_dist))
		return (FAIL);
	return (SUCCESS);
}

void	see_distraction(t_cub3d *cub3d, double dir_to_distraction, int i)
{
	double	angle_min;
	double	angle_max;
	double	max_dist;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	max_dist = sqrt(pow(cub3d->player.pos.x
				- cub3d->level->distractions[i].pos.x, 2)
			+ pow(cub3d->player.pos.y
				- cub3d->level->distractions[i].pos.y, 2));
	cub3d->level->distractions[i].visible = FALSE;
	if (angle_max < angle_min)
	{
		if (!do_distraction_max_smaller(cub3d, dir_to_distraction, max_dist))
			return ;
	}
	else
	{
		if (!do_distraction_min_smaller(cub3d, dir_to_distraction, max_dist))
			return ;
	}
	cub3d->level->distractions[i].visible = TRUE;
	draw_distraction(cub3d, dir_to_distraction, i);
	return ;
}
