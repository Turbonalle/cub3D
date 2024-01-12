/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_is_hit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:41:13 by slampine          #+#    #+#             */
/*   Updated: 2024/01/12 14:45:02 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	player_is_invulnerable(cub3d_t *cub3d)
{
	return (mlx_get_time() - cub3d->player.hit_timestamp
		< INVULNERABILITY_TIME);
}

void	player_is_hit(cub3d_t *cub3d, int i)
{
	if (cub3d->player.is_dirty_cheater == 1 || player_is_invulnerable(cub3d))
	{
		printf("Player is invulnerable!\n");
		return ;
	}
	cub3d->enemy[i].freeze_start = cub3d->run_time;
	cub3d->player.hit_timestamp = mlx_get_time();
	cub3d->player.health -= 1;
	activate_halo(&cub3d->halo, RED);
	adjust_hearts(cub3d);
}
