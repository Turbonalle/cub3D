/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_hover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:31:58 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:50 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	hover_minimap(t_cub3d *cub3d)
{
	int	mouse_x;
	int	mouse_y;

	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
	return (mouse_x >= cub3d->minimap.pos.x
		&& mouse_x <= cub3d->minimap.pos.x + cub3d->minimap.width
		&& mouse_y >= cub3d->minimap.pos.y
		&& mouse_y <= cub3d->minimap.pos.y + cub3d->minimap.height);
}
