/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:59:09 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 12:49:35 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	update_end(cub3d_t *cub3d, double dir, ray_t *ray)
{
	dvector_t	v_ray_dir;

	v_ray_dir.x = cos(dir);
	v_ray_dir.y = sin(dir);
	ray->end.x = cub3d->player.pos.x + v_ray_dir.x * ray->length;
	ray->end.y = cub3d->player.pos.y + v_ray_dir.y * ray->length;
}

void	adjust(vector_t *c_pos, ray_t *ray, vector_t v_step, dvector_t *ray_len)
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

void	adjust_wall_flag(dvector_t *ray_len, dvector_t d_step, int *wall_flag)
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

static dvector_t	shorten_vector(dvector_t pos, dvector_t target)
{
	dvector_t	len_target;
	dvector_t	result;

	len_target.x = target.x - pos.x;
	len_target.y = target.y - pos.y;
	result.x = pos.x + (0.95 * len_target.x);
	result.y = pos.y + (0.95 * len_target.y);
	return (result);
}

ray_t	*cast_ray(cub3d_t *cub3d, ray_t *ray)
{
	dvector_t	d_step;
	dvector_t	ray_len;
	vector_t	c_pos;
	vector_t	v_step;

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
