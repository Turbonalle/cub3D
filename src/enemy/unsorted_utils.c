/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsorted_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:23:58 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	ray_to_key(t_cub3d *cub3d, double dir_to, double max_dist)
{
	t_dvector		v_ray_step_size;
	t_dvector		v_ray_1d_length;
	t_vector		v_map_check;
	t_vector		v_step;
	t_ray			*ray;

	v_map_check.x = (int)cub3d->player.pos.x;
	v_map_check.y = (int)cub3d->player.pos.y;
	v_ray_step_size = init_step_size(to_radians(dir_to));
	v_step = init_v_step(dir_to);
	v_ray_1d_length = init_len(cub3d->player.pos,
			dir_to, v_map_check, v_ray_step_size);
	ray = init_ray_dir(dir_to);
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

static void	draw_key(t_cub3d *cub3d, double dir_to, t_key_node *key)
{
	double	dir_as_rad;
	int		i;

	i = 1;
	dir_as_rad = to_radians(dir_to);
	key->visible = TRUE;
	while (i < (int)cub3d->img->width - 1)
	{
		if (dir_as_rad == cub3d->rays[i].angle)
			break ;
		if (dir_as_rad > cub3d->rays[i].angle
			&& dir_as_rad < cub3d->rays[i + 1].angle)
			break ;
		i++;
	}
	key->dist_to_player = dist_between_d_vectors(key->pos, cub3d->player.pos);
	key->pos_screen.x = i;
	key->pos_screen.y = cub3d->img->height / 2
		+ (cub3d->img->height / 2) / key->dist_to_player * 2;
}

void	see_key(t_cub3d *cub3d, double dir_to, t_key_node *key)
{
	double	angle_min;
	double	angle_max;
	double	max_dist;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	max_dist = dist_between_d_vectors(key->pos, cub3d->player.pos);
	key->visible = FALSE;
	if (angle_max < angle_min)
	{
		if (cub3d->fov < 360 && dir_to > angle_max && dir_to < angle_min)
			return ;
		else if (ray_to_key(cub3d, dir_to, max_dist))
			draw_key(cub3d, dir_to, key);
	}
	else
	{
		if (cub3d->fov < 360 && (dir_to < angle_min || dir_to > angle_max))
			return ;
		else if (ray_to_key(cub3d, dir_to, max_dist))
			draw_key(cub3d, dir_to, key);
	}
	return ;
}

int	find_index(t_cub3d *cub3d)
{
	int		i;

	i = 1;
	while (i < (int)cub3d->img->width - 1)
	{
		if (cub3d->rays[i].angle > cub3d->rays[i + 1].angle)
			break ;
		i++;
	}
	return (i);
}
