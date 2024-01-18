/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:48:01 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:53:43 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static t_ray	*init_ray(t_enemy *enemy, int i)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->angle = enemy[i].dir_player;
	ray->length = 0;
	ray->target = 0;
	ray->wall = 0;
	ray->door_dir = 0;
	ray->end.x = 0;
	ray->end.y = 0;
	return (ray);
}

static void	set_enemy_angle_and_target(t_cub3d *cub3d, t_enemy *enemy,
	t_ray *ray)
{
	enemy->angle = to_radians(ray->angle);
	enemy->target = cub3d->player.pos;
}

int	enemy_ray(t_cub3d *cub3d, t_player player, t_enemy *enemy, int i)
{
	t_dvector		v_ray_step_size;
	t_dvector		v_ray_1d_length;
	t_vector		v_map_check;
	t_vector		v_step;
	t_ray			*ray;

	v_map_check.x = (int)enemy[i].pos.x;
	v_map_check.y = (int)enemy[i].pos.y;
	v_ray_step_size = init_step_size(to_radians(enemy[i].dir_player));
	v_step = init_v_step(enemy[i].dir_player);
	v_ray_1d_length = init_len(cub3d->enemy[i].pos, enemy[i].dir_player,
			v_map_check, v_ray_step_size);
	ray = init_ray(enemy, i);
	if (!ray)
		return (FAIL);
	while (not_at_end(ray, player, enemy, i))
	{
		if (wall_or_door_found(cub3d, v_map_check))
			return (free(ray), FAIL);
		adjust(&v_map_check, ray, v_step, &v_ray_1d_length);
		adjust_no_flag(&v_ray_1d_length, v_ray_step_size);
	}
	set_enemy_angle_and_target(cub3d, &enemy[i], ray);
	free(ray);
	return (SUCCESS);
}
