/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_draw_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:18:56 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 13:28:21 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

ray_t	*init_ray_dir(double dir_to_enemy)
{
	ray_t	*ray;

	ray = malloc(sizeof(ray_t));
	if (!ray)
		return (NULL);
	ray->angle = to_radians(dir_to_enemy);
	ray->length = 0;
	ray->target = 0;
	ray->wall = 0;
	ray->door_dir = 0;
	ray->end.x = 0;
	ray->end.y = 0;
	return (ray);
}

void	draw_distraction(cub3d_t *cub3d, double dir_to_distraction, int index)
{
	double	dir_as_rad;
	int		i;

	i = 1;
	dir_as_rad = to_radians(dir_to_distraction);
	while (i < (int)cub3d->img->width - 1)
	{
		if (dir_as_rad >= cub3d->rays[i].angle
			&& dir_as_rad < cub3d->rays[i + 1].angle)
			break ;
		i++;
	}
	if (dir_as_rad == 0)
		i = find_index(cub3d);
	cub3d->level->distractions[index].dist_to_player
		= dist_between_d_vectors(cub3d->level->distractions[index].pos,
			cub3d->player.pos);
	cub3d->level->distractions[index].pos_screen.x = i;
	cub3d->level->distractions[index].pos_screen.y
		= cub3d->img->height / 2 + (cub3d->img->height / 2)
		/ cub3d->level->distractions[index].dist_to_player * 2;
}
