/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:16:12 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/15 23:16:15 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	handle_cursor(cub3d_t *cub3d)
{
	vector_t	mouse_pos;

	if (cub3d->settings.mouse == TRUE && cub3d->state == STATE_GAME)
	{
		mlx_set_cursor_mode(cub3d->mlx, MLX_MOUSE_DISABLED);
		printf("Mouse active!\n");
	}
	else
		mlx_set_cursor_mode(cub3d->mlx, MLX_MOUSE_NORMAL);
	mlx_get_mouse_pos(cub3d->mlx, &mouse_pos.x, &mouse_pos.y);
	cub3d->mouse_set_pos.x = mouse_pos.x;
}
