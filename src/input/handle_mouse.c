/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:08:49 by slampine          #+#    #+#             */
/*   Updated: 2023/11/20 09:08:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void hook_mouse_buttons(enum mouse_key key, enum action action, enum modifier_key modifier, void *param)
{
	cub3d_t *cub3d;

	cub3d = param;
    (void)modifier;
	if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		cub3d->keys.mouse_left = TRUE;
		if (hover_minimap(cub3d))
		{
			cub3d->on_minimap = TRUE;
			cub3d->mouse_set_pos.x = cub3d->mouse.x;
			cub3d->mouse_set_pos.y = cub3d->mouse.y;
			cub3d->orig_minimap_pos.x = cub3d->minimap.pos.x;
			cub3d->orig_minimap_pos.y = cub3d->minimap.pos.y;
		}
		else
			cub3d->on_minimap = FALSE;
	}
    else if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		cub3d->keys.mouse_left = FALSE;
    else if (key == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		cub3d->keys.mouse_right = TRUE;
    else if (key == MLX_MOUSE_BUTTON_RIGHT && action == MLX_RELEASE)
		cub3d->keys.mouse_right = FALSE;
}

void hook_mouse_scroll(double xdelta, double ydelta, void *param)
{
	cub3d_t *cub3d;

	(void)xdelta;
	cub3d = param;
	if (ydelta > 0 && hover_minimap(cub3d))
		zoom_in_minimap(cub3d);
	else if (ydelta < 0 && hover_minimap(cub3d))
		zoom_out_minimap(cub3d);
}
