/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:32 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 13:28:39 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	draw_enemy(cub3d_t *cub3d, double dir_to_enemy, int index)
{
	double	dir_as_rad;
	int		i;

	i = 1;
	dir_as_rad = to_radians(dir_to_enemy);
	while (i < (int)cub3d->img->width - 1)
	{
		if (dir_as_rad >= cub3d->rays[i].angle
			&& dir_as_rad < cub3d->rays[i + 1].angle)
			break ;
		i++;
	}
	if (dir_as_rad == 0)
		i = find_index(cub3d);
	cub3d->enemy[index].dist_to_player
		= dist_between_d_vectors(cub3d->enemy[index].pos, cub3d->player.pos);
	cub3d->enemy[index].pos_screen.x = i;
	cub3d->enemy[index].pos_screen.y
		= cub3d->img->height / 2 + (cub3d->img->height / 2)
		/ cub3d->enemy[index].dist_to_player * 2;
}

void	enemy_visibility_max_smaller(cub3d_t *cub3d, int i,
	double max_dist, double dir_to_enemy)
{
	double	angle_min;
	double	angle_max;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	if (cub3d->fov < 360 && dir_to_enemy > angle_max
		&& dir_to_enemy < angle_min)
	{
		if (cub3d->enemy[i].is_hunting)
			enemy_cursor(cub3d, dir_to_enemy,
				dist_between_d_vectors(cub3d->enemy[i].pos, cub3d->player.pos));
	}
	else if (ray_to_enemy(cub3d, dir_to_enemy, max_dist))
	{
		cub3d->enemy[i].visible = TRUE;
		draw_enemy(cub3d, dir_to_enemy, i);
	}
}

void	enemy_visibility_min_smaller(cub3d_t *cub3d, int i,
	double max_dist, double dir_to_enemy)
{
	double	angle_min;
	double	angle_max;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	if (cub3d->fov < 360 && (dir_to_enemy < angle_min
			|| dir_to_enemy > angle_max))
	{
		if (cub3d->enemy[i].is_hunting)
			enemy_cursor(cub3d, dir_to_enemy,
				dist_between_d_vectors(cub3d->enemy[i].pos, cub3d->player.pos));
	}
	else if (ray_to_enemy(cub3d, dir_to_enemy, max_dist))
	{
		cub3d->enemy[i].visible = TRUE;
		draw_enemy(cub3d, dir_to_enemy, i);
	}
}

void	see_enemy(cub3d_t *cub3d, int i)
{
	double	angle_min;
	double	angle_max;
	double	max_dist;
	double	dir_to_enemy;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	max_dist = dist_between_d_vectors(cub3d->player.pos, cub3d->enemy[i].pos);
	dir_to_enemy = within_360((atan2(cub3d->enemy[i].pos.y
					- cub3d->player.pos.y, cub3d->enemy[i].pos.x
					- cub3d->player.pos.x) * 180 / M_PI));
	cub3d->enemy[i].visible = FALSE;
	if (angle_max < angle_min)
	{
		enemy_visibility_max_smaller(cub3d, i, max_dist, dir_to_enemy);
	}
	else
	{
		enemy_visibility_min_smaller(cub3d, i, max_dist, dir_to_enemy);
	}
	return ;
}
