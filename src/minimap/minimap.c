/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:27:18 by slampine          #+#    #+#             */
/*   Updated: 2023/11/15 14:27:19 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void update_minimap_fov(cub3d_t *cub3d)
{
	if (cub3d->keys.up)
		decrease_fov(cub3d);
	if (cub3d->keys.down)
		increase_fov(cub3d);
}

void update_minimap_player_pos(cub3d_t *cub3d)
{
	cub3d->minimap.player_pos.x = cub3d->player.pos.x * cub3d->minimap.tile_size;
	cub3d->minimap.player_pos.y = cub3d->player.pos.y * cub3d->minimap.tile_size;
}

void minimap(cub3d_t *cub3d)
{
	update_minimap_fov(cub3d);
	update_minimap_player_pos(cub3d);
	draw_minimap(cub3d);
	draw_minimap_border(cub3d);
	draw_fov(cub3d);
	draw_minimap_player(cub3d);
	draw_minimap_playerdir(cub3d);
}