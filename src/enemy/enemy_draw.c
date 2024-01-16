/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:40:19 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 23:58:10 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	set_enemy_properties(cub3d_t *cub3d, int index, int i)
{
	cub3d->enemy[index].dist_to_player = dist_between_d_vectors(
			cub3d->enemy[index].pos, cub3d->player.pos);
	cub3d->enemy[index].pos_screen.x = i;
	cub3d->enemy[index].pos_screen.y = cub3d->img->height / 2
		+ (cub3d->img->height / 2)
		/ cub3d->enemy[index].dist_to_player * 2;
}

void	draw_enemy(cub3d_t *cub3d, double dir_to_enemy, int index)
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
	{
		i = 1;
		while (i < (int)cub3d->img->width - 1)
		{
			if (cub3d->rays[i].angle > cub3d->rays[i + 1].angle)
				break ;
			i++;
		}
	}
	set_enemy_properties(cub3d, index, i);
}
