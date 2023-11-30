/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:08:49 by slampine          #+#    #+#             */
/*   Updated: 2023/11/28 14:01:18 by jbagger          ###   ########.fr       */
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
		if (cub3d->state == STATE_GAME)
		{
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
		else if (cub3d->state == STATE_PAUSE)
		{
			if (hover_any_box(cub3d, &cub3d->pause_menu))
				update_pause_settings(cub3d, &cub3d->pause_menu);
		}
		else if (cub3d->state == STATE_START)
		{
			if (hover_button(cub3d, &cub3d->start_menu.button_start))
			{
				cub3d->state = STATE_GAME;
				delete_start_menu(cub3d, &cub3d->start_menu);
				start_timer(cub3d);
			}
			else if (hover_button(cub3d, &cub3d->start_menu.button_level))
			{
				cub3d->state = STATE_LEVEL;
				delete_start_menu(cub3d, &cub3d->start_menu);
				draw_level_menu(cub3d, &cub3d->level_menu);
			}
			// else if (hover_button(cub3d, &cub3d->start_menu.button_settings))
			// {
			// 	cub3d->state = STATE_SETTINGS;
			// 	mlx_destroy_image(cub3d->mlx, cub3d->start_menu.img);
			// 	init_settings(cub3d);
			// }
			else if (hover_button(cub3d, &cub3d->start_menu.button_exit))
				mlx_close_window(cub3d->mlx);
		}
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
