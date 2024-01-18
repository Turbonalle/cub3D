/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:04:19 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:50 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	move_minimap_x(t_cub3d *cub3d)
{
	t_vector	mouse_moved;

	mouse_moved.x = cub3d->mouse.x - cub3d->mouse_set_pos.x;
	mouse_moved.y = cub3d->mouse.y - cub3d->mouse_set_pos.y;
	if (cub3d->orig_minimap_pos.x + mouse_moved.x < 0)
		cub3d->minimap.img->instances[0].x = 0;
	else if (cub3d->orig_minimap_pos.x + mouse_moved.x + cub3d->minimap.width
		> (int)cub3d->img->width)
	{
		cub3d->minimap.img->instances[0].x
			= cub3d->img->width - cub3d->minimap.width;
	}
	else
	{
		cub3d->minimap.img->instances[0].x
			= cub3d->orig_minimap_pos.x + mouse_moved.x;
	}
	cub3d->minimap.pos.x = cub3d->minimap.img->instances[0].x;
}

void	move_minimap_y(t_cub3d *cub3d)
{
	t_vector	mouse_moved;

	mouse_moved.x = cub3d->mouse.x - cub3d->mouse_set_pos.x;
	mouse_moved.y = cub3d->mouse.y - cub3d->mouse_set_pos.y;
	if (cub3d->orig_minimap_pos.y + mouse_moved.y < 0)
	{
		cub3d->minimap.img->instances[0].y = 0;
	}
	else if (cub3d->orig_minimap_pos.y + mouse_moved.y + cub3d->minimap.height
		> (int)cub3d->img->height)
	{
		cub3d->minimap.img->instances[0].y
			= cub3d->img->height - cub3d->minimap.height;
	}
	else
	{
		cub3d->minimap.img->instances[0].y
			= cub3d->orig_minimap_pos.y + mouse_moved.y;
	}
	cub3d->minimap.pos.y = cub3d->minimap.img->instances[0].y;
}
