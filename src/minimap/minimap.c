/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:31:00 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:50 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	update_minimap_fov(t_cub3d *cub3d)
{
	if (cub3d->settings.fisheye == 1)
	{
		if (cub3d->keys.up)
			decrease_fov(cub3d);
		if (cub3d->keys.down)
			increase_fov(cub3d);
	}
}

void	update_minimap_player_pos(t_cub3d *cub3d)
{
	cub3d->minimap.player_pos.x
		= cub3d->player.pos.x * cub3d->minimap.tile_size;
	cub3d->minimap.player_pos.y
		= cub3d->player.pos.y * cub3d->minimap.tile_size;
}

void	update_minimap_enemy_pos(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->num_enemies)
	{
		cub3d->enemy[i].minimap_pos.x
			= cub3d->enemy[i].pos.x * cub3d->minimap.tile_size;
		cub3d->enemy[i].minimap_pos.y
			= cub3d->enemy[i].pos.y * cub3d->minimap.tile_size;
		i++;
	}
}

void	minimap(t_cub3d *cub3d)
{
	update_minimap_fov(cub3d);
	update_minimap_player_pos(cub3d);
	draw_minimap(cub3d);
	draw_minimap_border(cub3d);
	draw_fov(cub3d);
	draw_minimap_player(cub3d);
	update_minimap_enemy_pos(cub3d);
	draw_minimap_playerdir(cub3d);
}
