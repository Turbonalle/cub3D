/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:16:12 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 11:09:35 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	handle_cursor(t_cub3d *cub3d)
{
	t_vector	mouse_pos;

	if (cub3d->settings.mouse == TRUE && cub3d->state == STATE_GAME)
		mlx_set_cursor_mode(cub3d->mlx, MLX_MOUSE_DISABLED);
	else
		mlx_set_cursor_mode(cub3d->mlx, MLX_MOUSE_NORMAL);
	mlx_get_mouse_pos(cub3d->mlx, &mouse_pos.x, &mouse_pos.y);
	cub3d->mouse_set_pos.x = mouse_pos.x;
}
