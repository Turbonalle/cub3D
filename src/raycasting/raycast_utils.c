/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:00:01 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 09:00:03 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../incl/cub3d.h"

void	raycasting(cub3d_t *cub3d)
{
	double			fov_start;
	double			max_dist;
	unsigned int	i;

	fov_start = within_two_pi(cub3d->player.angle - to_radians((cub3d->fov
					/ 2)));
	i = 0;
	max_dist = sqrt(cub3d->img->width * cub3d->img->width + cub3d->img->height
			* cub3d->img->height);
	while (i < cub3d->img->width)
	{
		cub3d->rays[i].angle = within_two_pi(fov_start
				+ to_radians((cub3d->fov * i / cub3d->img->width)));
		raycast(cub3d, &cub3d->player, &cub3d->rays[i], max_dist);
		i++;
	}
}

void	set_wall_direction(ray_t *ray, player_t *player, int wall_flag)
{
	if (wall_flag == X && player->pos.x < ray->end.x)
		ray->wall = WE;
	else if (wall_flag == X && ray->end.x < player->pos.x)
		ray->wall = EA;
	else if (wall_flag == Y && player->pos.y < ray->end.y)
		ray->wall = NO;
	else
		ray->wall = SO;
}

void	set_door_direction(ray_t *ray, player_t *player, int wall_flag)
{
	if (wall_flag == X && player->pos.x < ray->end.x)
		ray->door_dir = WE;
	else if (wall_flag == X && ray->end.x < player->pos.x)
		ray->door_dir = EA;
	else if (wall_flag == Y && player->pos.y < ray->end.y)
		ray->door_dir = NO;
	else
		ray->door_dir = SO;
	ray->wall = ray->target;
}

static void	reveal_hidden(cub3d_t *cub3d, vector_t v_map_check)
{
	if (v_map_check.x >= 0 && v_map_check.x
		< cub3d->level->map_columns && v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& (cub3d->level->map[v_map_check.y][v_map_check.x] == 'h'))
		cub3d->level->map[v_map_check.y][v_map_check.x] = '0';
	if (v_map_check.x >= 0 && v_map_check.x
		< cub3d->level->map_columns && v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& (cub3d->level->map[v_map_check.y][v_map_check.x] == 'r'))
		cub3d->level->map[v_map_check.y][v_map_check.x] = 'm';
	if (v_map_check.x >= 0 && v_map_check.x
		< cub3d->level->map_columns && v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& (cub3d->level->map[v_map_check.y][v_map_check.x] == 'o'))
		cub3d->level->map[v_map_check.y][v_map_check.x] = '1';
}

void	raycast(cub3d_t *cub3d, player_t *player, ray_t *ray, double max_dist)
{
	dvector_t	d_step;
	dvector_t	ray_len;
	vector_t	v_map_check;
	vector_t	v_step;
	int			wall_flag;

	d_step = init_step_size(ray->angle);
	v_map_check.x = (int)player->pos.x;
	v_map_check.y = (int)player->pos.y;
	reveal_hidden(cub3d, v_map_check);
	v_step = init_v_step(ray->angle * 180 / M_PI);
	ray_len = init_ray_1D_length(cub3d->player.pos,
			ray->angle * 180 / M_PI, v_map_check, d_step);
	while (ray->length < max_dist)
	{
		adjust(&v_map_check, ray, v_step, &ray_len);
		adjust_wall_flag(&ray_len, d_step, &wall_flag);
		reveal_hidden(cub3d, v_map_check);
		if (obstacle_found(cub3d, v_map_check, ray, ray->angle))
			break ;
	}
	if (ray->target == WALL)
		set_wall_direction(ray, player, wall_flag);
	else
		set_door_direction(ray, player, wall_flag);
}
