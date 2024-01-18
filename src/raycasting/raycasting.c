/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:59:09 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:53:43 by slampine         ###   ########.fr       */
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

void	adjust(t_vector *c_pos, t_ray *ray, t_vector v_step, t_dvector *ray_len)
{
	if (ray_len->x < ray_len->y)
	{
		c_pos->x += v_step.x;
		ray->length = ray_len->x;
	}
	else
	{
		c_pos->y += v_step.y;
		ray->length = ray_len->y;
	}
}

void	adjust_wall_flag(t_dvector *ray_len, t_dvector d_step, int *wall_flag)
{
	if (ray_len->x < ray_len->y)
	{
		ray_len->x += d_step.x;
		*wall_flag = X;
	}
	else
	{
		ray_len->y += d_step.y;
		*wall_flag = Y;
	}
}

static t_dvector	shorten_vector(t_dvector pos, t_dvector target)
{
	t_dvector	len_target;
	t_dvector	result;

	len_target.x = target.x - pos.x;
	len_target.y = target.y - pos.y;
	result.x = pos.x + (0.95 * len_target.x);
	result.y = pos.y + (0.95 * len_target.y);
	return (result);
}

t_ray	*cast_ray(t_cub3d *cub3d, t_ray *ray)
{
	t_dvector	d_step;
	t_dvector	ray_len;
	t_vector	c_pos;
	t_vector	v_step;

	d_step = init_step_size(cub3d->player.angle);
	c_pos.x = (int)cub3d->player.pos.x;
	c_pos.y = (int)cub3d->player.pos.y;
	v_step = init_v_step(ray->angle * 180 / M_PI);
	ray_len = init_len(cub3d->player.pos,
			cub3d->player.angle * 180 / M_PI, c_pos, d_step);
	while (ray->length < DISTRACTION_THROW_DISTANCE)
	{
		adjust(&c_pos, ray, v_step, &ray_len);
		adjust_no_flag(&ray_len, d_step);
		if (obstacle_found(cub3d, c_pos, ray, cub3d->player.angle))
			break ;
	}
	update_end(cub3d, cub3d->player.angle, ray);
	ray->end = shorten_vector(cub3d->player.pos, ray->end);
	return (ray);
}
