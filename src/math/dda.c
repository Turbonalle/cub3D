/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:42:54 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	update_player_vertically(t_cub3d *cub3d, t_player *player,
	t_dvector end, int dist)
{
	t_vector	check;

	player->new_pos.x = player->pos.x;
	check.x = player->pos.x;
	check.y = player->pos.y;
	if (check.y < end.y)
	{
		while (check.y < end.y)
		{
			if (obstacle_found_dist(cub3d, check, dist))
				player->new_pos.y = player->pos.y;
			check.y += 1;
		}
	}
	else if (check.y > end.y)
	{
		while (check.y > end.y)
		{
			if (obstacle_found_dist(cub3d, check, dist))
				player->new_pos.y = player->pos.y;
			check.y -= 1;
		}
	}
}

void	update_player_horizontally(t_cub3d *cub3d, t_player *player,
	t_dvector end, int dist)
{
	t_vector	check;

	player->new_pos.y = player->pos.y;
	check.x = player->pos.x;
	check.y = player->pos.y;
	if (check.x < end.x)
	{
		while (check.x < end.x)
		{
			if (obstacle_found_dist(cub3d, check, dist))
				player->new_pos.x = player->pos.x;
			check.x += 1;
		}
	}
	else if (check.x > end.x)
	{
		while (check.x > end.x)
		{
			if (obstacle_found_dist(cub3d, check, dist))
				player->new_pos.x = player->pos.x;
			check.x -= 1;
		}
	}
}

void	move_x_step(t_cub3d *cub3d, t_player *player, t_dvector end, int *wall)
{
	cub3d->raycast.v_map_check.x += cub3d->raycast.v_step.x;
	cub3d->raycast.dist = cub3d->raycast.v_ray_1d_length.x;
	cub3d->raycast.v_ray_1d_length.x += cub3d->raycast.v_ray_step_size.x;
	if (cub3d->raycast.dist < cub3d->raycast.delta
		&& obstacle_found_dist(cub3d, cub3d->raycast.v_map_check,
			cub3d->raycast.dist))
	{
		update_player_vertically(cub3d, player, end, cub3d->raycast.dist);
		*wall = wall_checker(1, end, player->pos);
	}
}

void	move_y_step(t_cub3d *cub3d, t_player *player, t_dvector end, int *wall)
{
	cub3d->raycast.v_map_check.y += cub3d->raycast.v_step.y;
	cub3d->raycast.dist = cub3d->raycast.v_ray_1d_length.y;
	cub3d->raycast.v_ray_1d_length.y += cub3d->raycast.v_ray_step_size.y;
	if (cub3d->raycast.dist < cub3d->raycast.delta
		&& obstacle_found_dist(cub3d, cub3d->raycast.v_map_check,
			cub3d->raycast.dist))
	{
		update_player_horizontally(cub3d, player, end, cub3d->raycast.dist);
		*wall = wall_checker(0, end, player->pos);
	}
}

int	find_end_point(t_cub3d *cub3d, t_player *player, double radians,
	t_dvector end)
{
	int		wall;

	wall = NO_WALL;
	if (cub3d->level->map[(int)player->pos.y][(int)player->pos.x] == WALL)
		return (FAIL);
	cub3d->raycast.delta = dist_between_d_vectors(player->pos, end);
	cub3d->raycast.v_ray_step_size = init_step_size(radians);
	cub3d->raycast.v_map_check.x = (int)player->pos.x;
	cub3d->raycast.v_map_check.y = (int)player->pos.y;
	cub3d->raycast.v_step = init_v_step(radians * 180 / M_PI);
	cub3d->raycast.v_ray_1d_length = init_len(player->pos, radians * 180
			/ M_PI, cub3d->raycast.v_map_check, cub3d->raycast.v_ray_step_size);
	cub3d->raycast.dist = 0;
	while (cub3d->raycast.dist < cub3d->raycast.delta)
	{
		if (cub3d->raycast.v_ray_1d_length.x < cub3d->raycast.v_ray_1d_length.y)
			move_x_step(cub3d, player, end, &wall);
		else
			move_y_step(cub3d, player, end, &wall);
		if (wall != NO_WALL)
			return (wall);
	}
	return (NO_WALL);
}
