/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_draw_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:42:31 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 22:51:06 by vvagapov         ###   ########.fr       */
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

static void	set_distraction_properties(cub3d_t *cub3d, int index, int i)
{
	cub3d->level->distractions[index].dist_to_player
		= dist_between_d_vectors(cub3d->level->distractions[index].pos,
			cub3d->player.pos);
	cub3d->level->distractions[index].pos_screen.x = i;
	cub3d->level->distractions[index].pos_screen.y
		= cub3d->img->height / 2 + (cub3d->img->height / 2)
		/ cub3d->level->distractions[index].dist_to_player * 2;
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
	{
		i = 1;
		while (i < (int)cub3d->img->width - 1)
		{
			if (cub3d->rays[i].angle > cub3d->rays[i + 1].angle)
				break ;
			i++;
		}
	}
	set_distraction_properties(cub3d, index, i);
}
