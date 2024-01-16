/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:02:25 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 22:14:38 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	eat(cub3d_t *cub3d, int i)
{
	if (cub3d->enemy[i].target.x != cub3d->level->distraction.x
		|| cub3d->enemy[i].target.y != cub3d->level->distraction.y)
		cub3d->enemy[i].is_eating = 0;
	cub3d->level->distraction_amount -= ENEMY_EATING_SPEED;
	if (cub3d->level->distraction_amount <= 0)
	{
		cub3d->player.thrown = FALSE;
		cub3d->level->distractions[cub3d->level->num_distractions]
			.img_distraction->instances[0].enabled = FALSE;
		cub3d->enemy[i].is_eating = 0;
	}
}

int	not_at_end(ray_t *ray, player_t player, t_enemy *enemy, int i)
{
	double	max_dist;

	max_dist = sqrt(pow(player.pos.x - enemy[i].pos.x, 2)
			+ pow(player.pos.y - enemy[i].pos.y, 2));
	if (ray->length < max_dist)
		return (1);
	return (0);
}
