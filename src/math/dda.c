/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:42:54 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 21:12:58 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	all_keys_found(cub3d_t *cub3d, int i)
{
	key_node_t	*temp;

	temp = cub3d->level->key_groups[i].keys;
	while (temp != NULL)
	{
		if (temp->collected == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

static int	obstacle_found_dist(cub3d_t *cub3d, vector_t v_map_check,
	int dist)
{
	if (v_map_check.x >= 0
		&& v_map_check.x < cub3d->level->map_columns
		&& v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& (cub3d->level->map[v_map_check.y][v_map_check.x] == WALL
	))
		return (1);
	if (v_map_check.x >= 0 && v_map_check.x < cub3d->level->map_columns
		&& v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& (cub3d->level->map[v_map_check.y][v_map_check.x] == 'A'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'B'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'C'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'D'))
	{
		if (dist > 1)
			return (1);
		if (check_if_door_unlocked(cub3d, v_map_check.x, v_map_check.y))
			return (0);
		else
			return (1);
	}
	return (0);
}

int	wall_checker(int wall_flag, dvector_t end, dvector_t pos)
{
	if (wall_flag == 1 && end.x > pos.x)
		return (WE);
	else if (wall_flag == 1)
		return (EA);
	else if (wall_flag == 0 && pos.y < end.y)
		return (NO);
	else if (wall_flag == 0 && pos.y >= end.y)
		return (SO);
	else
		return (0);
}

int	find_end_point(cub3d_t *cub3d, player_t *player, double radians,
	dvector_t end)
{
	dvector_t	v_ray_step_size;
	dvector_t	v_ray_1d_length;
	vector_t	v_map_check;
	vector_t	v_step;
	double		dist;
	double		delta;
	int			wall;

	if (cub3d->level->map[(int)player->pos.y][(int)player->pos.x] == WALL)
		return (0);
	delta = dist_between_d_vectors(player->pos, end);
	v_ray_step_size = init_step_size(radians);
	v_map_check.x = (int)player->pos.x;
	v_map_check.y = (int)player->pos.y;
	v_step = init_v_step(radians * 180 / M_PI);
	v_ray_1d_length = init_len(player->pos, radians * 180 / M_PI, v_map_check, v_ray_step_size);

	wall = 0;
	dist = 0;
	while (dist < delta)
	{
		if (v_ray_1d_length.x < v_ray_1d_length.y)
		{
			v_map_check.x += v_step.x;
			dist = v_ray_1d_length.x;
			v_ray_1d_length.x += v_ray_step_size.x;
			if (dist < delta && obstacle_found_dist(cub3d, v_map_check, dist))
			{
				player->new_pos.x = player->pos.x;
				wall = wall_checker(1, end, player->pos);
				vector_t check;
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
				return (wall);
			}
		}
		else
		{
			v_map_check.y += v_step.y;
			dist = v_ray_1d_length.y;
			v_ray_1d_length.y += v_ray_step_size.y;
			if (dist < delta && obstacle_found_dist(cub3d, v_map_check, dist))
			{
				player->new_pos.y = player->pos.y;
				wall = wall_checker(0, end, player->pos);
				vector_t check;
				check.x = player->pos.x;
				check.y = player->pos.y;
				if (check.x < end.x)
				{
					while (++check.x < end.x)
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
				return (wall);
			}
		}
	}
	return (wall);
}

dvector_t	init_step_size(double angle)
{
	dvector_t	v_ray_step_size;
	dvector_t	v_ray_dir;

	v_ray_dir.x = cos(angle);
	v_ray_dir.y = sin(angle);
	v_ray_step_size.x = sqrt(1 + (v_ray_dir.y / v_ray_dir.x) * (v_ray_dir.y
				/ v_ray_dir.x));
	v_ray_step_size.y = sqrt(1 + (v_ray_dir.x / v_ray_dir.y) * (v_ray_dir.x
				/ v_ray_dir.y));
	return (v_ray_step_size);
}
