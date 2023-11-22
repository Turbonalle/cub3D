/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:04:10 by slampine          #+#    #+#             */
/*   Updated: 2023/11/22 13:19:14 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"
int enemy_staring_point(cub3d_t *cub3d)
{
	int	i;
	int	j;

	i = -1;
	while (cub3d->map[++i])
	{
		j = -1;
		while (cub3d->map[i][++j])
		{
			if (cub3d->map[i][j] == 'F')
			{
				cub3d->enemy[0].pos.x = j;
				cub3d->enemy[0].pos.y = i;
				cub3d->enemy[0].angle = 0;
				cub3d->map[i][j] = '0';
				return (SUCCESS);
			}
		}
	}
	return (FAIL);
}

int enemy(cub3d_t *cub3d)
{
	int	num_enemies;

	num_enemies = 1;
	cub3d->enemy = malloc(sizeof(t_enemy) * num_enemies);
	cub3d->enemy[0].angle = 0;
	cub3d->enemy[0].is_spinning = 0;
	cub3d->enemy[0].is_walking = 0;
	cub3d->enemy[0].dir.x = 0;
	cub3d->enemy[0].dir.y = 0;
	enemy_staring_point(cub3d);
	return (0);
}