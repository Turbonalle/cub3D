/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_additional.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:16:11 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 13:16:30 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	see_keys(cub3d_t *cub3d, int i)
{
	double		dir_to_key;
	key_node_t	*temp;

	temp = cub3d->level->key_groups[i].keys;
	while (temp)
	{
		dir_to_key = within_360((atan2(temp->pos.y - cub3d->player.pos.y,
						temp->pos.x - cub3d->player.pos.x) * 180 / M_PI));
		if (temp->collected == 0)
			see_key(cub3d, dir_to_key, temp);
		temp = temp->next;
	}
}

static void	check_distraction(cub3d_t *cub3d, int i)
{
	double		dir_to_distraction;

	dir_to_distraction = within_360((atan2(cub3d->level->distractions[i].pos.y
					- cub3d->player.pos.y, cub3d->level->distractions[i].pos.x
					- cub3d->player.pos.x) * 180 / M_PI));
	if (cub3d->level->distractions[i].collected == FALSE)
		see_distraction(cub3d, dir_to_distraction, i);
}

void	draw_enemies(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->num_enemies)
	{
		see_enemy(cub3d, i);
		i++;
	}
	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		if (cub3d->level->door_groups[i].num_keys_left)
		{
			see_keys(cub3d, i);
		}
		i++;
	}
	i = 0;
	while (i < cub3d->level->num_distractions + cub3d->player.thrown)
	{
		check_distraction(cub3d, i);
		i++;
	}
}
